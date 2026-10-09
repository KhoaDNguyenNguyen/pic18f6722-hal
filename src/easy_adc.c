#include "easy_adc.h"
#include "adc.h"
#include <math.h>

void Easy_ADC_Init(void) {
    ADC_Init();
}

uint16_t Easy_ADC_ReadRaw(uint8_t channel, uint8_t samples) {
    if (samples == 0) samples = 1;
    uint32_t sum = 0;
    for (uint8_t i = 0; i < samples; i++) {
        sum += ADC_Read(channel);
    }
    return (uint16_t)(sum / samples);
}

float Easy_LM35_Read(uint8_t channel, uint8_t samples) {
    uint16_t raw = Easy_ADC_ReadRaw(channel, samples);
    return (float)raw / 2.046f;
}

float Easy_Sharp_Read(uint8_t channel, uint8_t samples) {
    uint16_t raw = Easy_ADC_ReadRaw(channel, samples);
    if (raw == 0) return 80.0f;
    float dist = pow(4277.0f / (float)raw, 1.106f);
    if (dist > 80.0f) dist = 80.0f;
    if (dist < 10.0f) dist = 10.0f;
    return dist;
}
