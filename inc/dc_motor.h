#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include <stdint.h>

void DCMotor_Init(void);
void DCMotor_SetPWM(int16_t duty);
void DCMotor_Coast(void);
void DCMotor_Brake(void);

#endif
