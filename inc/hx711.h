#ifndef HX711_H
#define HX711_H

#include <stdint.h>

void HX711_Init(void);
int32_t HX711_Read(void);
int32_t HX711_ReadAverage(uint8_t times);

#endif
