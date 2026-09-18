#ifndef GLCD_H
#define GLCD_H

#include <stdint.h>

void GLCD_Init(void);
void GLCD_Clear(void);
void GLCD_SetCursor(uint8_t row, uint8_t col);
void GLCD_Print(const char* str);
void GLCD_PrintInt(int32_t val);

#endif
void GLCD_Command(uint8_t cmd);
void GLCD_Data(uint8_t data);
