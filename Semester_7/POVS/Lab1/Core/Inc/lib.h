#ifndef LIB_DECLARATION
#define LIB_DECLARATION
#include "stm32f1xx_hal.h"

#define DELAY_TIME 1000
#define CORRECTION_TIME 100
extern volatile int isUnPressed;

extern volatile int previousUnPressedTime;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif // LIB_DECLARATION
