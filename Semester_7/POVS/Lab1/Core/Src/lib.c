#include "lib.h"
volatile int isUnPressed = 0;
volatile int previousUnPressedTime = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if((GPIO_Pin == GPIO_PIN_13) && (HAL_GetTick() - previousUnPressedTime) > CORRECTION_TIME)
   {
      isUnPressed = 1;
		  previousUnPressedTime = HAL_GetTick();
   }
}
