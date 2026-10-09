#include "step_motor.h"
#include "buzzer.h"

void StepMotor_Init(void) {
    Actuator_SetMask(0x0780, 0x0000);
}

void StepMotor_Step(uint8_t step_idx) {
    static const uint16_t fs[4] = {0x0700, 0x0680, 0x0580, 0x0380};
    Actuator_SetMask(0x0780, fs[step_idx & 0x03]);
}
