#include "lib.h"
#include "main.h"
#include "display.h"

volatile int previousUnPressedTime = 0;

unsigned int seed = 12345;

unsigned int lcg() {
    seed = (1103515245 * seed + 12345) % 2147483648;
    return seed;
}

int random_number(int min, int max) {
    return (lcg() % (max - min + 1)) + min;
}

uint8_t data = 0;
Buffer displayBuffer = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if(GPIO_Pin == GPIO_PIN_1 && (HAL_GetTick() - previousUnPressedTime) > CORRECTION_TIME)
   {
		 data = (uint8_t) random_number(1, 6);
		 HAL_UART_Transmit_IT(&huart2, &data, sizeof(uint8_t));
		 previousUnPressedTime = HAL_GetTick();
		 pushNumberIntoBuffer(&displayBuffer, data);
		 printNumberOnDisplay(&displayBuffer);
   }
	 else if (GPIO_Pin == GPIO_PIN_4 && (HAL_GetTick() - previousUnPressedTime) > CORRECTION_TIME)
	 {
		 data = 0;
		 HAL_UART_Transmit_IT(&huart2, &data, sizeof(uint8_t));
		 previousUnPressedTime = HAL_GetTick();
		 pushNumberIntoBuffer(&displayBuffer, data);
		 printNumberOnDisplay(&displayBuffer);
	 }
}

