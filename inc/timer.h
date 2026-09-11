#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>

extern volatile bool tmr3_1s_flag;

void Timer_Init(void);
uint32_t Timer_GetMillis(void);
void Timer3_ClearFlag(void);

#endif
