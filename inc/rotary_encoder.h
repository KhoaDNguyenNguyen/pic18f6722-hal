#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <stdint.h>

void RotaryEncoder_Init(void);
int32_t RotaryEncoder_GetValue(void);
void RotaryEncoder_Update(void);

#endif
