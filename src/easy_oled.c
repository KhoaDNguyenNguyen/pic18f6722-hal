#include "easy_oled.h"
#include "oled.h"
#include "glcd.h"

void Easy_OLED_Init(void) {
    OLED_Init();
}

void Easy_OLED_ShowImage(const uint8_t* img) {
    OLED_DrawBitmap(img);
    OLED_Update();
}

void Easy_GLCD_ShowImage(const uint8_t* img) {
    uint16_t idx = 0;
    for(uint8_t y = 0; y < 32; y++) {
        GLCD_Command(0x80 + y);
        GLCD_Command(0x80);
        for(uint8_t x = 0; x < 16; x++) {
            GLCD_Data(img[idx++]);
        }
    }
    for(uint8_t y = 0; y < 32; y++) {
        GLCD_Command(0x80 + y);
        GLCD_Command(0x88);
        for(uint8_t x = 0; x < 16; x++) {
            GLCD_Data(img[idx++]);
        }
    }
}
