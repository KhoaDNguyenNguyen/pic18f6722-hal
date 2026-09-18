#include "lcd.h"
#include "hardware.h"
#include "config.h"

#ifdef TARGET_SIMULATION

void LCD_Command(uint8_t cmd) {
    LCD_RS = 0;
    LCD_DATA = cmd;
    LCD_E = 1;
    __delay_us(10);
    LCD_E = 0;
    if (cmd < 4) __delay_ms(2);
    else __delay_us(50);
}

void LCD_Data(uint8_t data) {
    LCD_RS = 1;
    LCD_DATA = data;
    LCD_E = 1;
    __delay_us(10);
    LCD_E = 0;
    __delay_us(50);
}

void LCD_Init(void) {
    ADCON1 = 0x0F;
    TRIS_LCD_DATA = 0x00;
    TRIS_LCD_RS = 0;
    TRIS_LCD_E = 0;
    
    LCD_RS = 0;
    LCD_E = 0;
    LCD_DATA = 0x00;

    __delay_ms(50);
    LCD_Command(0x30);
    __delay_ms(5);
    LCD_Command(0x30);
    __delay_ms(1);
    LCD_Command(0x30);
    __delay_ms(1);
    LCD_Command(0x38);
    LCD_Command(0x0C);
    LCD_Command(0x01);
    LCD_Command(0x06);
}

void LCD_Clear(void) {
    LCD_Command(0x01);
    __delay_ms(5);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t addrs[] = {0x80, 0xC0, 0x94, 0xD4};
    if (row < 4 && col < 20) LCD_Command(addrs[row] + col);
}

void LCD_Print(const char* str) {
    while (*str) LCD_Data((uint8_t)*str++);
}

void LCD_PrintInt(int32_t val) {
    char buf[12];
    char* p = buf + 11;
    *p = '\0';
    uint8_t is_neg = 0;
    if (val < 0) { is_neg = 1; val = -val; }
    if (val == 0) *--p = '0';
    else {
        do { *--p = (char)((val % 10) + '0'); val /= 10; } while (val > 0);
    }
    if (is_neg) *--p = '-';
    LCD_Print(p);
}

void LCD_PrintPad2(uint8_t val) {
    char buf[3];
    buf[0] = (val / 10) + '0';
    buf[1] = (val % 10) + '0';
    buf[2] = '\0';
    LCD_Print(buf);
}

void LCD_PrintTime(uint8_t h, uint8_t m, uint8_t s) {
    LCD_PrintPad2(h); LCD_Print(":");
    LCD_PrintPad2(m); LCD_Print(":");
    LCD_PrintPad2(s);
}

#else

#include "mbi5026.h"

static void LCD_Send(uint8_t rs, uint8_t data) {
    uint8_t ctrl = 0x00;
    if (rs) ctrl |= 0x04;

    uint8_t buf[2];
    buf[1] = ~(ctrl | 0x01);
    buf[0] = ~data;
    MBI_WriteData(buf, 2, MBI_LE3_LCD);
    __delay_us(20);
    
    buf[1] = ~ctrl;
    buf[0] = ~data;
    MBI_WriteData(buf, 2, MBI_LE3_LCD);
    __delay_us(50);
}

void LCD_Command(uint8_t cmd) { LCD_Send(0x00, cmd); }
void LCD_Data(uint8_t data) { LCD_Send(0x01, data); }

void LCD_Init(void) {
    __delay_ms(50);
    LCD_Command(0x30); __delay_ms(5);
    LCD_Command(0x30); __delay_us(200);
    LCD_Command(0x30); __delay_us(200);
    LCD_Command(0x38); __delay_us(200);
    LCD_Command(0x0C); __delay_us(200);
    LCD_Command(0x01); __delay_ms(5);
    LCD_Command(0x06); __delay_ms(5);
}

void LCD_Clear(void) {
    LCD_Command(0x01);
    __delay_ms(5);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t addrs[] = {0x80, 0xC0, 0x94, 0xD4};
    if (row < 4 && col < 20) {
        LCD_Command(addrs[row] + col);
    }
}

void LCD_Print(const char* str) {
    while (*str) LCD_Data((uint8_t)*str++);
}

void LCD_PrintInt(int32_t val) {
    char buf[12];
    char* p = buf + 11;
    *p = '\0';
    uint8_t is_neg = 0;
    if (val < 0) { is_neg = 1; val = -val; }
    if (val == 0) *--p = '0';
    else {
        do { *--p = (char)((val % 10) + '0'); val /= 10; } while (val > 0);
    }
    if (is_neg) *--p = '-';
    LCD_Print(p);
}

void LCD_PrintPad2(uint8_t val) {
    char buf[3];
    buf[0] = (val / 10) + '0';
    buf[1] = (val % 10) + '0';
    buf[2] = '\0';
    LCD_Print(buf);
}

void LCD_PrintTime(uint8_t h, uint8_t m, uint8_t s) {
    LCD_PrintPad2(h); LCD_Print(":");
    LCD_PrintPad2(m); LCD_Print(":");
    LCD_PrintPad2(s);
}

#endif
