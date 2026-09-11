#include "counter.h"
#include "hardware.h"

void Counter_Init(void) {
#ifndef TARGET_SIMULATION
    TRIS_SENSOR_HY860F = 1;
    T0CON = 0x28; 
    Counter_Reset();
    Counter_Start();
#endif
}

void Counter_Start(void) {
#ifndef TARGET_SIMULATION
    T0CONbits.TMR0ON = 1;
#endif
}

void Counter_Stop(void) {
#ifndef TARGET_SIMULATION
    T0CONbits.TMR0ON = 0;
#endif
}

uint16_t Counter_Get(void) {
#ifdef TARGET_SIMULATION
    static uint16_t sim_val = 0;
    sim_val++;
    return sim_val;
#else
    uint8_t l = TMR0L;
    uint8_t h = TMR0H;
    return ((uint16_t)h << 8) | l;
#endif
}

void Counter_Set(uint16_t val) {
#ifndef TARGET_SIMULATION
    TMR0H = (uint8_t)(val >> 8);
    TMR0L = (uint8_t)(val & 0xFF);
#endif
}

void Counter_Reset(void) {
    Counter_Set(0);
}
