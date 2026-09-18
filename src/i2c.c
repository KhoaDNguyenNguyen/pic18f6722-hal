#include "i2c.h"
#include "config.h"

void I2C_Init(void) {
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    SSP1CON1 = 0x28; // I2C Master mode
    SSP1CON2 = 0x00;
    SSP1STAT = 0x00;
    SSP1ADD = 49;    // 100kHz at 20MHz
}

static uint8_t I2C_Wait(void) {
    uint16_t timeout = 10000;
    while ((SSP1CON2 & 0x1F) || (SSP1STATbits.R_nW)) {
        if (--timeout == 0) return 0; // Tránh treo MCU nếu I2C lỗi
    }
    return 1;
}

void I2C_Start(void) {
    if(!I2C_Wait()) return;
    SSP1CON2bits.SEN = 1;
}

void I2C_Stop(void) {
    if(!I2C_Wait()) return;
    SSP1CON2bits.PEN = 1;
}

void I2C_Write(uint8_t data) {
    if(!I2C_Wait()) return;
    SSP1BUF = data;
}

uint8_t I2C_Read(uint8_t ack) {
    uint8_t temp = 0;
    if(!I2C_Wait()) return 0;
    SSP1CON2bits.RCEN = 1;
    if(!I2C_Wait()) return 0;
    temp = SSP1BUF;
    if(!I2C_Wait()) return temp;
    SSP1CON2bits.ACKDT = (ack) ? 0 : 1;
    SSP1CON2bits.ACKEN = 1;
    return temp;
}
