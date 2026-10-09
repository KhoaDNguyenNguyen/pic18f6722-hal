#include "adc.h"
#include "hardware.h"
#include "config.h"

void ADC_Init(void) {
#ifndef TARGET_SIMULATION
    TRISA |= 0x2F;
    ADCON1 = 0x0A;
    ADCON2 = 0xAE;
    ADCON0bits.ADON = 1;
#endif
}

uint16_t ADC_Read(uint8_t channel) {
#ifdef TARGET_SIMULATION
    static uint16_t sim_val = 0;
    sim_val = (sim_val + 5) % 1024;
    return sim_val;
#else
    if (channel > 15) return 0;
    ADCON0 &= 0xC3;
    ADCON0 |= (uint8_t)(channel << 2);
    __delay_us(20);
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO);
    return ((uint16_t)ADRESH << 8) | ADRESL;
#endif
}