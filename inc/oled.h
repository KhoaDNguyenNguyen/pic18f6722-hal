#ifndef OLED_H
#define OLED_H

#include <stdint.h>

void OLED_Init(void);
void OLED_Command(uint8_t cmd);
void OLED_Clear(void);
void OLED_Update(void);
void OLED_DrawBitmap(const uint8_t* bitmap);

#endif
