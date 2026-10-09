#ifndef EASY_MOTOR_H
#define EASY_MOTOR_H

#include <stdint.h>
#include <stdbool.h>

void Easy_DCMotor_SetPWM(int16_t duty);

void Easy_StepMotor_Run(bool forward, uint32_t rpm);
void Easy_StepMotor_Stop(void);
void Easy_StepMotor_Task(void);

void Easy_Servo_SetAngle(uint8_t angle);

#endif
