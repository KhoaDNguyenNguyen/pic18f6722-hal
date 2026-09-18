#include "ds1307.h"
#include "i2c.h"

#define DS1307_ADDR 0xD0

static uint8_t dec2bcd(uint8_t val) {
    return (uint8_t)(((val / 10) << 4) | (val % 10));
}

static uint8_t bcd2dec(uint8_t val) {
    return (uint8_t)(((val >> 4) * 10) + (val & 0x0F));
}

void DS1307_Init(void) {
    I2C_Init();
}

void DS1307_SetDateTime(uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint8_t year) {
    I2C_Start();
    I2C_Write(DS1307_ADDR);
    I2C_Write(0x00);
    I2C_Write(dec2bcd(sec)); // Ghi giây (CH bit = 0 để khởi động dao động)
    I2C_Write(dec2bcd(min));
    I2C_Write(dec2bcd(hour));
    I2C_Write(dec2bcd(day));
    I2C_Write(dec2bcd(date));
    I2C_Write(dec2bcd(month));
    I2C_Write(dec2bcd(year));
    I2C_Stop();
}

void DS1307_GetDateTime(uint8_t *sec, uint8_t *min, uint8_t *hour, uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year) {
    I2C_Start();
    I2C_Write(DS1307_ADDR);
    I2C_Write(0x00);
    I2C_Stop();

    I2C_Start();
    I2C_Write(DS1307_ADDR | 1);
    *sec = bcd2dec(I2C_Read(1) & 0x7F);
    *min = bcd2dec(I2C_Read(1));
    *hour = bcd2dec(I2C_Read(1) & 0x3F);
    *day = bcd2dec(I2C_Read(1));
    *date = bcd2dec(I2C_Read(1));
    *month = bcd2dec(I2C_Read(1));
    *year = bcd2dec(I2C_Read(0));
    I2C_Stop();
}
