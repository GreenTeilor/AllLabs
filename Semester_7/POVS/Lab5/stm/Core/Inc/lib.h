#ifndef LIB_DECLARATION
#define LIB_DECLARATION
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"

#define CORRECTION_TIME 500

extern volatile int previousJumpPressedTime;
extern volatile int previousShootPressedTime;
extern volatile int previousRunPressedTime;

extern volatile uint16_t adc;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

#endif // LIB_DECLARATION
