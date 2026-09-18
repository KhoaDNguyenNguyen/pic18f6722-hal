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
#include "lcd.h"
#include "glcd.h"

const uint8_t cgram_bignum[64] = {
    0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
    0x1F,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,0x1F,
    0x1F,0x1F,0x1F,0x00,0x00,0x1F,0x1F,0x1F,
    0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x00,0x00,
    0x00,0x00,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const uint8_t bignum_map[10][6] = {
    {0,1,0,0,2,0}, {1,0,6,2,0,2}, {3,3,0,0,2,2}, {1,3,0,2,2,0},
    {0,2,0,6,6,0}, {0,3,3,2,2,0}, {0,3,3,0,2,0}, {1,1,0,6,6,0},
    {0,3,0,0,2,0}, {0,3,0,2,2,0}
};

void Easy_LCD_InitBigNumbers(void) {
    LCD_Command(0x40);
    for(uint8_t i = 0; i < 64; i++) {
        LCD_Data(cgram_bignum[i]);
    }
    LCD_Command(0x80);
}

void Easy_LCD_PrintBigNum(uint8_t x, uint8_t y, uint8_t val) {
    if(val > 9) return;
    LCD_SetCursor(y, x);
    LCD_Data(bignum_map[val][0]);
    LCD_Data(bignum_map[val][1]);
    LCD_Data(bignum_map[val][2]);
    LCD_SetCursor(y + 1, x);
    LCD_Data(bignum_map[val][3]);
    LCD_Data(bignum_map[val][4]);
    LCD_Data(bignum_map[val][5]);
}

void Easy_GLCD_GraphicMode(uint8_t enable) {
    GLCD_Command(0x30);
    if(enable) {
        GLCD_Command(0x36);
    } else {
        GLCD_Command(0x30);
    }
}

void Easy_GLCD_DrawCheckerboard(void) {
    uint8_t pat1 = 0xAA;
    uint8_t pat2 = 0x55;
    for(uint8_t y = 0; y < 32; y++) {
        GLCD_Command(0x80 + y);
        GLCD_Command(0x80 + 0);
        for(uint8_t x = 0; x < 16; x++) {
            GLCD_Data((y % 2) ? pat1 : pat2);
            GLCD_Data((y % 2) ? pat1 : pat2);
        }
    }
    for(uint8_t y = 0; y < 32; y++) {
        GLCD_Command(0x80 + y);
        GLCD_Command(0x88 + 0);
        for(uint8_t x = 0; x < 16; x++) {
            GLCD_Data((y % 2) ? pat2 : pat1);
            GLCD_Data((y % 2) ? pat2 : pat1);
        }
    }
}
