#ifndef LIB_DECLARATION
#define LIB_DECLARATION
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include "math.h"
#include "stdio.h"
#include "string.h"

#define CORRECTION_TIME 500
#define PARAMETERS_COUNT 4
#define SAMPLING_RATE 100
#define PI acos(-1)
#define LOW_BORDER 1
#define HIGH_BORDER 9

typedef struct Pin
{
	GPIO_TypeDef* port;
	uint16_t line;
} Pin;

extern volatile int previousUnPressedTime;

extern volatile uint16_t adc;

extern volatile int activeParameter;

extern volatile int8_t parameters[4];

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif // LIB_DECLARATION
