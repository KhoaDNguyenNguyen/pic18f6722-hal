#ifndef COUNTER_H
#define COUNTER_H

#include <stdint.h>

void Counter_Init(void);
void Counter_Start(void);
void Counter_Stop(void);
uint16_t Counter_Get(void);
void Counter_Set(uint16_t val);
void Counter_Reset(void);

#endif
