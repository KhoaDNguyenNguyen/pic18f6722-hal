#ifndef DS1307_H
#define DS1307_H

#include <stdint.h>

void DS1307_Init(void);
void DS1307_SetDateTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void DS1307_GetDateTime(uint8_t *sec, uint8_t *min, uint8_t *hour, uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year);

#endif
