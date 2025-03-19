#include "lib.h"
#include "main.h"
#include "display.h"

volatile int previousUnPressedTime = 0;

volatile uint16_t adc = 0;

volatile int activeParameter = 0;

volatile int8_t parameters[4] = {1,1,1,1};

volatile int8_t* A = &parameters[0];
volatile int8_t* T = &parameters[1];
volatile int8_t* F = &parameters[2];
volatile int8_t* FI0 = &parameters[3];

uint8_t data = 0;
Buffer displayBuffer = 0;

uint8_t n = 0;

Pin selectPinByActiveParameter(int activeParameter);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin == GPIO_PIN_1 && (HAL_GetTick() - previousUnPressedTime) > CORRECTION_TIME)
   {
		  Pin previousLed = selectPinByActiveParameter(activeParameter);
		  HAL_GPIO_WritePin(previousLed.port, previousLed.line, GPIO_PIN_SET);
		  activeParameter = (activeParameter + 1) % PARAMETERS_COUNT;
		  Pin newLed = selectPinByActiveParameter(activeParameter);
			HAL_GPIO_WritePin(newLed.port, newLed.line, GPIO_PIN_RESET);
		  
			pushNumberIntoBuffer(&displayBuffer, parameters[activeParameter]);
		  printNumberOnDisplay(&displayBuffer);
		 
			previousUnPressedTime = HAL_GetTick();
   }
	 else if (GPIO_Pin == GPIO_PIN_4 && (HAL_GetTick() - previousUnPressedTime) > CORRECTION_TIME)
	 {
			if (parameters[activeParameter] > LOW_BORDER)
			{
				parameters[activeParameter]--;
			}
		 
		  pushNumberIntoBuffer(&displayBuffer, parameters[activeParameter]);
		  printNumberOnDisplay(&displayBuffer);
		 
			previousUnPressedTime = HAL_GetTick();
	 }
	 else if (GPIO_Pin == GPIO_PIN_0 && (HAL_GetTick() - previousUnPressedTime) > CORRECTION_TIME)
	 {
		  if (parameters[activeParameter] < HIGH_BORDER)
			{
				parameters[activeParameter]++;
			}
		 
		  pushNumberIntoBuffer(&displayBuffer, parameters[activeParameter]);
		  printNumberOnDisplay(&displayBuffer);
		 
			previousUnPressedTime = HAL_GetTick();
	 }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		HAL_ADC_Start(&hadc1); 
		HAL_ADC_PollForConversion(&hadc1, 100); 
		adc = HAL_ADC_GetValue(&hadc1);
		HAL_ADC_Stop(&hadc1);
	
		n = (n + 1) % (SAMPLING_RATE + 1);
		double signal1 = (4 * (double)*A / *T) * fabs(fmod((double)n / SAMPLING_RATE, (double)*T) - (double)*T / 2)  - *A;
		double signal2 = (2 * *A / PI) * asin(sin(2 * PI * *F * ((double)n / SAMPLING_RATE) + *FI0));
			
		char firstSignalStr[50];
		char secondSignalStr[15];
		char adcStr[15];
		snprintf((char*)firstSignalStr, sizeof(firstSignalStr), "%f,", signal1);
		snprintf((char*)secondSignalStr, sizeof(secondSignalStr), "%f,",signal2);
		snprintf(adcStr, sizeof(adcStr), "%d\n", (uint16_t)adc);
		strcat(firstSignalStr, secondSignalStr);
		strcat(firstSignalStr, adcStr);
		HAL_UART_Transmit_DMA(&huart2, (uint8_t*)firstSignalStr, strlen(firstSignalStr));	 
}

Pin createPin(GPIO_TypeDef* port, uint16_t line)
{
	return (Pin){ port, line };
}

Pin selectPinByActiveParameter(int activeParameter)
{
	 switch (activeParameter)
	 {
		 case 0:
			 return createPin(GPIOA, GPIO_PIN_5);
		 case 1:
			 return createPin(GPIOA, GPIO_PIN_6);
		 case 2: 
			 return createPin(GPIOA, GPIO_PIN_7);
	   case 3:
			 return createPin(GPIOB, GPIO_PIN_6);
		 default:
			 return createPin(GPIOA, GPIO_PIN_5);
	 }
}

