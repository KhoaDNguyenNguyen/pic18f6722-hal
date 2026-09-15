#include "easy_screen.h"
#include "all.h"
#include <stdio.h>
#include <stdarg.h>

void Easy_LCD_PrintString(uint8_t x, uint8_t y, const char* str) {
    LCD_SetCursor(y, x);
    LCD_Print(str);
}

void Easy_LCD_PrintNum(uint8_t x, uint8_t y, int32_t val) {
    LCD_SetCursor(y, x);
    LCD_PrintInt(val);
}

void Easy_LCD_ClearLine(uint8_t y) {
    LCD_SetCursor(y, 0);
    LCD_Print("                    ");
}

void Easy_LCD_PrintFormat(uint8_t x, uint8_t y, const char* format, ...) {
    char buffer[32];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    LCD_SetCursor(y, x);
    LCD_Print(buffer);
}

void Easy_GLCD_PrintString(uint8_t x, uint8_t y, const char* str) {
    GLCD_SetCursor(y, x);
    GLCD_Print(str);
}

void Easy_GLCD_PrintNum(uint8_t x, uint8_t y, int32_t val) {
    GLCD_SetCursor(y, x);
    GLCD_PrintInt(val);
}

void Easy_GLCD_ClearLine(uint8_t y) {
    GLCD_SetCursor(y, 0);
    GLCD_Print("                ");
}

void Easy_GLCD_PrintFormat(uint8_t x, uint8_t y, const char* format, ...) {
    char buffer[32];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    GLCD_SetCursor(y, x);
    GLCD_Print(buffer);
}

void Easy_LCD_CreateChar(uint8_t loc, const uint8_t* map) {
    loc &= 0x07;
    LCD_Command(0x40 | (loc << 3));
    for(uint8_t i = 0; i < 8; i++) {
        LCD_Data(map[i]);
    }
    LCD_Command(0x80);
}
