#ifndef EASY_OLED_H
#define EASY_OLED_H

#include <stdint.h>

void Easy_OLED_Init(void);
void Easy_OLED_ShowImage(const uint8_t* img);
void Easy_GLCD_ShowImage(const uint8_t* img);

#endif
