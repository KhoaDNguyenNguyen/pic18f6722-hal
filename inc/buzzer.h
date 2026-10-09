#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include <stdbool.h>

void Actuator_SetBit(uint8_t bit_pos, bool state);
void Actuator_SetMask(uint16_t mask, uint16_t val);

void Buzzer_Init(void);
void Buzzer_Set(bool state);
void Relay1_Set(bool state);
void Relay2_Set(bool state);
void Triac1_Set(bool state);
void Triac2_Set(bool state);

#endif
