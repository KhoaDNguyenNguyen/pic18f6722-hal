#ifndef EASY_DHT_H
#define EASY_DHT_H

#include <stdint.h>

void Easy_DHT_Init(void);
void Easy_DHT_Update(void);
uint8_t Easy_DHT_GetTemp(void);
uint8_t Easy_DHT_GetHumi(void);

#endif
