#include "dc_motor.h"
#include "hardware.h"
#include "config.h"

void DCMotor_Init(void) {
#ifndef TARGET_SIMULATION
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    // Pre-engage active braking to prevent freewheeling upon initialization
    LATCbits.LATC1 = 1;
    LATCbits.LATC2 = 1;

    PR2 = 0xFF;
    T2CON = 0x06; 
    CCP1CON = 0x00;
    CCP2CON = 0x00;
#endif
}

void DCMotor_SetPWM(int16_t duty) {
#ifndef TARGET_SIMULATION
    if (duty == 0) {
        CCP1CON = 0x00;
        CCP2CON = 0x00;
        // Output HIGH to both pins triggers active H-Bridge braking via optocouplers
        LATCbits.LATC1 = 1;
        LATCbits.LATC2 = 1;
        return;
    }

    uint16_t abs_duty = (duty > 0) ? duty : -duty;
    if (abs_duty > 1023) abs_duty = 1023;

    if (duty > 0) {
        CCP2CON = 0x00;
        LATCbits.LATC1 = 0;
        
        CCPR1L = (uint8_t)(abs_duty >> 2);
        CCP1CON = (uint8_t)(((abs_duty & 0x03) << 4) | 0x0C);
    } else {
        CCP1CON = 0x00;
        LATCbits.LATC2 = 0;
        
        CCPR2L = (uint8_t)(abs_duty >> 2);
        CCP2CON = (uint8_t)(((abs_duty & 0x03) << 4) | 0x0C);
    }
#endif
}

void DCMotor_Coast(void) {
#ifndef TARGET_SIMULATION
    CCP1CON = 0x00;
    CCP2CON = 0x00;
    // Output LOW to both pins disconnects optocouplers, causing the motor to coast
    LATCbits.LATC1 = 0;
    LATCbits.LATC2 = 0;
#endif
}
