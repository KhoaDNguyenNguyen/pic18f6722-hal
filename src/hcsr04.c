#include "hcsr04.h"
#include "sensor_pins.h"
#include "config.h"

void HCSR04_Init(void) {
    TRIS_HCSR04_TRIG = 0;
    TRIS_HCSR04_ECHO = 1;
    HCSR04_TRIG_LAT = 0;
}

uint16_t HCSR04_Read(void) {
    uint32_t ticks = 0;
    uint16_t timeout = 60000;
    uint8_t gie = INTCONbits.GIE;
    
    INTCONbits.GIE = 0;

    HCSR04_TRIG_LAT = 1;
    __delay_us(20);
    HCSR04_TRIG_LAT = 0;

    while (!HCSR04_ECHO_PIN) {
        if (--timeout == 0) {
            INTCONbits.GIE = gie;
            return 0;
        }
    }
    
    while (HCSR04_ECHO_PIN) {
        ticks++;
        __delay_us(1);
        if (ticks > 25000) break; 
    }

    INTCONbits.GIE = gie;
    return (uint16_t)((ticks * 16) / 580); 
}
