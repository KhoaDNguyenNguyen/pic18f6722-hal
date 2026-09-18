#ifndef EASY_RTC_H
#define EASY_RTC_H

#include <stdint.h>

void Easy_RTC_Init(void);
void Easy_RTC_SetTime(uint8_t hour, uint8_t min, uint8_t sec);
void Easy_RTC_SetDate(uint8_t date, uint8_t month, uint8_t year, uint8_t day);
void Easy_RTC_Read(void);

uint8_t Easy_RTC_GetHour(void);
uint8_t Easy_RTC_GetMinute(void);
uint8_t Easy_RTC_GetSecond(void);
uint8_t Easy_RTC_GetDay(void);
uint8_t Easy_RTC_GetDate(void);
uint8_t Easy_RTC_GetMonth(void);
uint8_t Easy_RTC_GetYear(void);

#endif
