#include "sharp_gp2y.h"
#include "adc.h"
#include <math.h>

void Sharp_Init(void) {
    ADC_Init();
}

uint16_t Sharp_Read(uint8_t channel) {
    uint32_t sum = 0;
    
    for (uint8_t i = 0; i < 10; i++) {
        sum += ADC_Read(channel);
    }
    
    uint16_t avg = sum / 10;

    if (avg < 30) return 80;

    float dist = pow(4277.0f / (float)avg, 1.106f);
    
    if (dist > 80.0f) dist = 80.0f;
    if (dist < 10.0f) dist = 10.0f;

    return (uint16_t)dist;
}
