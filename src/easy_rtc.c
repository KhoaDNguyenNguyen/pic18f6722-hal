#include "easy_rtc.h"
#include "ds1307.h"

static uint8_t r_sec, r_min, r_hour, r_day, r_date, r_month, r_year;

void Easy_RTC_Init(void) {
    DS1307_Init();
}

void Easy_RTC_SetTime(uint8_t hour, uint8_t min, uint8_t sec) {
    Easy_RTC_Read(); // Đọc dữ liệu cũ để không bị ghi đè rỗng ngày tháng
    DS1307_SetDateTime(sec, min, hour, r_day, r_date, r_month, r_year);
}

void Easy_RTC_SetDate(uint8_t date, uint8_t month, uint8_t year, uint8_t day) {
    Easy_RTC_Read(); // Đọc dữ liệu cũ để không bị ghi đè rỗng giờ giấc
    DS1307_SetDateTime(r_sec, r_min, r_hour, day, date, month, year);
}

void Easy_RTC_Read(void) {
    DS1307_GetDateTime(&r_sec, &r_min, &r_hour, &r_day, &r_date, &r_month, &r_year);
}

uint8_t Easy_RTC_GetHour(void) { return r_hour; }
uint8_t Easy_RTC_GetMinute(void) { return r_min; }
uint8_t Easy_RTC_GetSecond(void) { return r_sec; }
uint8_t Easy_RTC_GetDay(void) { return r_day; }
uint8_t Easy_RTC_GetDate(void) { return r_date; }
uint8_t Easy_RTC_GetMonth(void) { return r_month; }
uint8_t Easy_RTC_GetYear(void) { return r_year; }
