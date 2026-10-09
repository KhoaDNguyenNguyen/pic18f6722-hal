#ifndef EASY_ADC_H
#define EASY_ADC_H

#include <stdint.h>

#define ADC_CH_LM35A    4
#define ADC_CH_LM35B    0
#define ADC_CH_JOY_X    1
#define ADC_CH_JOY_Y    2
#define ADC_CH_SHARP    3

void Easy_ADC_Init(void);
uint16_t Easy_ADC_ReadRaw(uint8_t channel, uint8_t samples);
float Easy_LM35_Read(uint8_t channel, uint8_t samples);
float Easy_Sharp_Read(uint8_t channel, uint8_t samples);

#endif
