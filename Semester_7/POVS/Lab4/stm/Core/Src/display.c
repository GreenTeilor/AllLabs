#include "display.h"

const uint8_t digits[] = {
  0xC0, //0
  0xF9, //1
  0xA4, //2
  0xB0, //3
  0x99, //4
  0x92, //5
  0x82, //6
  0xF8, //7
  0x80, //8
  0x90  //9
};

const uint8_t segments[] = {
  0xF1,
  0xF2,
  0xF4,
  0xF8
};

uint8_t getDigitFromBuffer(const Buffer *buffer, int index) 
{
	return (*buffer >> (index * 4)) & 0x000F;
}

void pushDigitIntoBuffer(Buffer *buffer, int index, uint8_t digit) 
{
	*buffer |= (digit & 0x000F) << (index * 4);
}

void shiftRegister(uint8_t digitOrSegment)
{
  for (int i = 0; i < 8; i++)
  {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, digitOrSegment & 0x80 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    digitOrSegment <<= 1;
  }
}

void printDigitOnDisplay(uint8_t segment, uint8_t digit)
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
  shiftRegister(digits[digit]);
  shiftRegister(segments[segment]);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
}

void printNumberOnDisplay(const Buffer *buffer)
{
	for (int i = 0; i <= 3; i++)
	{
		printDigitOnDisplay(i, getDigitFromBuffer(buffer, i));
	}
}

void pushNumberIntoBuffer(Buffer *buffer, uint8_t number)
{
	*buffer = 0;
  for (int i = 3; i >= 0; i--)
  {
    pushDigitIntoBuffer(buffer, i, number % 10);
    number /= 10;
  }
}
