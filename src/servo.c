#include "servo.h"
#include "buzzer.h"
#include "config.h"
#include "timer.h"

static uint8_t current_angle = 255;
static uint32_t last_pulse_time = 0;

void Servo_Init(void) {
    Actuator_SetBit(6, false);
    current_angle = 255;
}

void Servo_SetAngle(uint8_t angle) {
    if (angle > 180) angle = 180;
    current_angle = angle;
}

void Servo_Task(void) {
    if (current_angle == 255) return;
    
    uint32_t now = Timer_GetMillis();
    if (now - last_pulse_time >= 20) {
        last_pulse_time = now;
        
        Actuator_SetBit(6, true);
        
        uint16_t loops = 100 + ((uint32_t)current_angle * 100) / 180; 
        for (uint16_t i = 0; i < loops; i++) {
            __delay_us(10);
        }
        
        Actuator_SetBit(6, false);
    }
}
