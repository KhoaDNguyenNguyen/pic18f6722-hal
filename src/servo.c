#include "servo.h"
#include "buzzer.h"
#include "config.h"

void Servo_Init(void) {
    Actuator_SetBit(6, false);
}

void Servo_Pulse(uint8_t angle) {
    if (angle > 180) angle = 180;
    Actuator_SetBit(6, true);
    
    uint16_t loops = 100 + ((uint32_t)angle * 100) / 180; 
    for (uint16_t i = 0; i < loops; i++) {
        __delay_us(10);
    }
    
    Actuator_SetBit(6, false);
}
