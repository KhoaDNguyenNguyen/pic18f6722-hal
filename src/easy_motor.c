#include "easy_motor.h"
#include "dc_motor.h"
#include "step_motor.h"
#include "servo.h"
#include "timer.h"

static bool step_running = false;
static bool step_dir = true;
static uint32_t step_interval = 0;
static uint32_t step_last = 0;
static uint8_t step_idx = 0;

void Easy_DCMotor_SetPWM(int16_t duty) {
    DCMotor_SetPWM(duty);
}

void Easy_DCMotor_Coast(void) {
    DCMotor_Coast();
}

void Easy_StepMotor_Run(bool forward, uint32_t rpm) {
    if (rpm == 0) {
        Easy_StepMotor_Stop();
        return;
    }
    step_running = true;
    step_dir = forward;
    
    step_interval = 60000 / (rpm * 200); 
    if (step_interval == 0) step_interval = 1;
    step_last = Timer_GetMillis();
}

void Easy_StepMotor_Stop(void) {
    step_running = false;
}

void Easy_StepMotor_Task(void) {
    if (!step_running) return;
    uint32_t now = Timer_GetMillis();
    if (now - step_last >= step_interval) {
        step_last = now;
        if (step_dir) step_idx++;
        else step_idx--;
        StepMotor_Step(step_idx);
    }
}

void Easy_Servo_SetAngle(uint8_t angle) {
    Servo_Pulse(angle);
}
