#ifndef EASY_WEIGHT_H
#define EASY_WEIGHT_H

#include <stdint.h>

void Easy_Weight_Init(void);
void Easy_Weight_Tare(void);
void Easy_Weight_SetFactor(float factor);
int32_t Easy_Weight_GetGrams(void);

#endif
