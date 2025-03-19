#ifndef LIB_DECLARATION
#define LIB_DECLARATION
#include "stm32f1xx_hal.h"

#define CORRECTION_TIME 500

extern volatile int previousUnPressedTime;

extern unsigned int seed;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
int random_number(int min, int max);

#endif // LIB_DECLARATION
