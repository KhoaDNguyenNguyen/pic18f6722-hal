#include "led7seg.h"
#include "mbi5026.h"

static const uint8_t LED7_HEX[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 
    0xFF, 0xBF 
};

static uint8_t led7_buf[8];

void LED7_Init(void) {
    LED7_Clear();
    LED7_Update();
}

void LED7_Clear(void) {
    for (uint8_t i = 0; i < 8; i++) {
        led7_buf[i] = 16;
    }
}

void LED7_DisplayInt(int32_t val) {
    LED7_Clear();
    uint8_t is_neg = 0;
    
    if (val < 0) {
        is_neg = 1;
        val = -val;
    }
    
    if (val == 0) {
        led7_buf[0] = 0;
        return;
    }
    
    uint8_t pos = 0;
    while (val > 0 && pos < 8) {
        led7_buf[pos++] = (uint8_t)(val % 10);
        val /= 10;
    }
    
    if (is_neg && pos < 8) {
        led7_buf[pos] = 17;
    }
}

void LED7_Update(void) {
    uint8_t out[8];
    for (uint8_t i = 0; i < 8; i++) {
        out[i] = ~LED7_HEX[led7_buf[i]];
    }
    MBI_WriteData(out, 8, MBI_LE1_LED7SEG);
}
