#ifndef DHT11_H
#define DHT11_H

#include <stdint.h>
#include <stdbool.h>

void DHT11_Init(void);
bool DHT11_Read(uint8_t* temp, uint8_t* humi);

#endif
