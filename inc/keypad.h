#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

void Keypad_Init(void);
uint8_t Keypad_ReadSingle(void);
uint16_t Keypad_ReadMask(void);

#endif
