#include "glcd.h"
#include "hardware.h"
#include "config.h"

#ifdef TARGET_SIMULATION

static void GLCD_Command(uint8_t cmd) {
    LCD_RS = 0;
    LCD_DATA = cmd;
    GLCD_E = 1;
    __delay_us(10);
    GLCD_E = 0;
    __delay_us(50);
}

static void GLCD_Data(uint8_t data) {
    LCD_RS = 1;
    LCD_DATA = data;
    GLCD_E = 1;
    __delay_us(10);
    GLCD_E = 0;
    __delay_us(50);
}

void GLCD_Init(void) {
    ADCON1 = 0x0F;
    TRIS_LCD_DATA = 0x00;
    TRIS_LCD_RS = 0;
    TRIS_GLCD_E = 0;
    TRIS_GLCD_CSA = 0;
    TRIS_GLCD_CSB = 0;
    TRIS_GLCD_CSC = 0;
    
    GLCD_E = 0;
    LCD_RS = 0;
    LCD_DATA = 0x00;
    GLCD_CSA = 0;
    GLCD_CSB = 0;
    GLCD_CSC = 0;

    __delay_ms(50);
    GLCD_Command(0x3E); 
    GLCD_Command(0x3F); 
}

void GLCD_Clear(void) {
    GLCD_Command(0x01);
    __delay_ms(15);
}

void GLCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t addrs[] = {0x80, 0x90, 0x88, 0x98};
    if (row < 4 && col < 8) GLCD_Command(addrs[row] + col);
}

void GLCD_Print(const char* str) {
    while (*str) GLCD_Data((uint8_t)*str++);
}

void GLCD_PrintInt(int32_t val) {
    char buf[12];
    char* p = buf + 11;
    *p = '\0';
    uint8_t is_neg = 0;
    if (val < 0) { is_neg = 1; val = -val; }
    if (val == 0) *--p = '0';
    else { do { *--p = (char)((val % 10) + '0'); val /= 10; } while (val > 0); }
    if (is_neg) *--p = '-';
    GLCD_Print(p);
}

#else

#include "mbi5026.h"

static void GLCD_Send(uint8_t rs, uint8_t data) {
    uint8_t ctrl = 0x03;
    if (rs) ctrl |= 0x10;

    uint8_t buf[2];
    buf[1] = ~(ctrl | 0x04);
    buf[0] = ~data;
    MBI_WriteData(buf, 2, MBI_LE4_GLCD);
    __delay_us(20);
    
    buf[1] = ~ctrl;
    buf[0] = ~data;
    MBI_WriteData(buf, 2, MBI_LE4_GLCD);
    __delay_us(50);
}

static void GLCD_Command(uint8_t cmd) { GLCD_Send(0x00, cmd); }
static void GLCD_Data(uint8_t data) { GLCD_Send(0x01, data); }

void GLCD_Init(void) {
    __delay_ms(50);
    GLCD_Command(0x30); __delay_ms(5);
    GLCD_Command(0x30); __delay_us(200);
    GLCD_Command(0x0C); __delay_us(200);
    GLCD_Command(0x01); __delay_ms(15);
    GLCD_Command(0x06); __delay_ms(5);
}

void GLCD_Clear(void) {
    GLCD_Command(0x01);
    __delay_ms(15);
}

void GLCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t addrs[] = {0x80, 0x90, 0x88, 0x98};
    if (row < 4 && col < 8) {
        GLCD_Command(addrs[row] + col);
    }
}

void GLCD_Print(const char* str) {
    while (*str) GLCD_Data((uint8_t)*str++);
}

void GLCD_PrintInt(int32_t val) {
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
    GLCD_Print(p);
}

#endif
