#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdint.h>

void LEDMatrix_Init(void);
void LEDMatrix_Clear(void);
void LEDMatrix_Print(const char* str, uint8_t color);
void LEDMatrix_Scan(void);

#endif
