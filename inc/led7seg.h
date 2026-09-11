#ifndef LED7SEG_H
#define LED7SEG_H

#include <stdint.h>

void LED7_Init(void);
void LED7_Clear(void);
void LED7_DisplayInt(int32_t val);
void LED7_Update(void);

#endif
