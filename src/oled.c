#include "oled.h"
#include "i2c.h"

#define OLED_ADDR 0x78
static uint8_t oled_buffer[1024];

void OLED_Command(uint8_t cmd) {
    I2C_Start();
    I2C_Write(OLED_ADDR);
    I2C_Write(0x00);
    I2C_Write(cmd);
    I2C_Stop();
}

void OLED_Init(void) {
    const uint8_t init_seq[] = {
        0xAE, 0xA8, 0x3F, 0xD3, 0x00, 0x40, 0xA0, 0xA1, 
        0xC0, 0xC8, 0xDA, 0x12, 0x81, 0xFF, 0xA4, 0xA6, 
        0xD5, 0x80, 0x8D, 0x14, 0xAF, 0x20, 0x00
    };
    
    for(uint8_t i = 0; i < sizeof(init_seq); i++) {
        OLED_Command(init_seq[i]);
    }
    
    OLED_Clear();
    OLED_Update();
}

void OLED_Clear(void) {
    for(uint16_t i = 0; i < 1024; i++) {
        oled_buffer[i] = 0;
    }
}

void OLED_DrawBitmap(const uint8_t* bitmap) {
    for(uint16_t i = 0; i < 1024; i++) {
        oled_buffer[i] = bitmap[i];
    }
}

void OLED_Update(void) {
    for(uint8_t page = 0; page < 8; page++) {
        OLED_Command(0xB0 + page);
        OLED_Command(0x00);
        OLED_Command(0x10);
        
        I2C_Start();
        I2C_Write(OLED_ADDR);
        I2C_Write(0x40);
        for(uint8_t i = 0; i < 128; i++) {
            I2C_Write(oled_buffer[page * 128 + i]);
        }
        I2C_Stop();
    }
}
