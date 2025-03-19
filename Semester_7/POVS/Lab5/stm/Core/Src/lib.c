#include "lib.h"
#include "main.h"
#include "display.h"

volatile int previousJumpPressedTime = 0;
volatile int previousShootPressedTime = 0;
volatile int previousRunPressedRime = 0;

volatile uint16_t adc = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin == GPIO_PIN_5 && (HAL_GetTick() - previousJumpPressedTime) > CORRECTION_TIME)
   {
	    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
			xTaskNotifyFromISR(butPressedHandle, GPIO_Pin, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);	
		 
			previousJumpPressedTime = HAL_GetTick();
   }
	 else if (GPIO_Pin == GPIO_PIN_4 && (HAL_GetTick() - previousShootPressedTime) > CORRECTION_TIME)
	 {
	    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
			xTaskNotifyFromISR(butPressedHandle, GPIO_Pin, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);	
		 
			previousShootPressedTime = HAL_GetTick();
	 } else if (GPIO_Pin == GPIO_PIN_3 && (HAL_GetTick() - previousRunPressedRime) > CORRECTION_TIME)
	 {
			BaseType_t xHigherPriorityTaskWoken = pdFALSE;
			xTaskNotifyFromISR(butPressedHandle, GPIO_Pin, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	
		  previousRunPressedRime = HAL_GetTick();
	 }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC1)
    {
			  adc = HAL_ADC_GetValue(&hadc1);
				if (adc >= 3500) 
				{
					const char* msg = "moveRight\n";
					HAL_UART_Transmit_DMA(&huart2, (uint8_t*)msg, strlen(msg));	
				} 
				else if (adc <=1500) 
				{
					const char* msg = "moveLeft\n";
					HAL_UART_Transmit_DMA(&huart2, (uint8_t*)msg, strlen(msg));		
				} 
				else if (adc > 1500 && adc < 3500) 
				{
					const char* msg = "stand\n";
					HAL_UART_Transmit_DMA(&huart2, (uint8_t*)msg, strlen(msg));
				}
        adc = 0;
    }
}
