#include "timer.h"
#include "config.h"
#include "rotary_encoder.h"

static volatile uint32_t sys_millis = 0;
static volatile uint8_t tmr3_ticks = 0;
volatile bool tmr3_1s_flag = false;

void Timer_Init(void) {
    T1CON = 0x81;
    TMR1H = 0xEC;
    TMR1L = 0x78;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;

    T3CON = 0xB1; 
    TMR3H = 0xE7; 
    TMR3L = 0x96;
    PIR2bits.TMR3IF = 0;
    PIE2bits.TMR3IE = 1;

    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

uint32_t Timer_GetMillis(void) {
    uint32_t ms;
    uint8_t gie_status = INTCONbits.GIE;
    INTCONbits.GIE = 0;
    ms = sys_millis;
    INTCONbits.GIE = gie_status;
    return ms;
}

void Timer3_ClearFlag(void) {
    tmr3_1s_flag = false;
}

void __interrupt() ISR(void) {
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        TMR1H = 0xEC;
        TMR1L = 0x78;
        sys_millis++;
        RotaryEncoder_Update();
    }
    
    if (PIE2bits.TMR3IE && PIR2bits.TMR3IF) {
        PIR2bits.TMR3IF = 0;
        TMR3H = 0xE7; 
        TMR3L = 0x96;
        tmr3_ticks++;
        if (tmr3_ticks >= 100) {
            tmr3_ticks = 0;
            tmr3_1s_flag = true;
        }
    }
}
