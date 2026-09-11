#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(const char* str);
void LCD_PrintInt(int32_t val);
void LCD_PrintPad2(uint8_t val);
void LCD_PrintTime(uint8_t h, uint8_t m, uint8_t s);

#endif
