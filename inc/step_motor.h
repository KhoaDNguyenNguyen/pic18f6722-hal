#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H

#include <stdint.h>

void StepMotor_Init(void);
void StepMotor_Step(uint8_t step_idx);

#endif
