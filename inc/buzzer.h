#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include <stdbool.h>

void Buzzer_Init(void);
void Buzzer_Set(bool state);
void Relay1_Set(bool state);
void Relay2_Set(bool state);
void Triac1_Set(bool state);
void Triac2_Set(bool state);

#endif
