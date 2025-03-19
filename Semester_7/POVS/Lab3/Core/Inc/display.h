#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "stm32f1xx_hal.h"
#include "main.h"

typedef uint16_t Buffer;

void pushNumberIntoBuffer(Buffer *buffer, uint8_t number);

void printNumberOnDisplay(const Buffer *buffer);

#endif
