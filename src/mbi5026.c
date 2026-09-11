#include "mbi5026.h"
#include "hardware.h"

#ifdef TARGET_SIMULATION

static void SPI_WriteByte(uint8_t data) {
    SPI_BUF = data;
    while (!SPI_STAT_BF);
    (void)SPI_BUF;
}

void MBI_Init(void) {
    ADCON1 = 0x0F;
    CMCON = 0x07;
    
    TRIS_SPI_SCK = 0;
    TRIS_SPI_SDO = 0;
    
    SPI_CON1 = 0x20;
    SPI_STAT = 0x40;

    TRIS_LATCH_LED = 0;
    TRIS_LATCH_7SEG = 0;
    
    LATCH_LED = 0;
    LATCH_7SEG = 0;

    MBI_ClearAll();
}

void MBI_WriteData(const uint8_t *data, uint8_t length, MBI_Latch_t latch) {
    if (latch == MBI_LE0_LED32 || latch == MBI_LE1_LED7SEG) {
        for (int8_t i = length - 1; i >= 0; i--) {
            SPI_WriteByte(data[i]);
        }
        if (latch == MBI_LE0_LED32) {
            LATCH_LED = 1; 
            __delay_us(2); 
            LATCH_LED = 0;
        } else {
            LATCH_7SEG = 1; 
            __delay_us(2); 
            LATCH_7SEG = 0;
        }
    }
}

void MBI_ClearAll(void) {
    uint8_t buf_00[8] = {0};
    MBI_WriteData(buf_00, 4, MBI_LE0_LED32);
    MBI_WriteData(buf_00, 8, MBI_LE1_LED7SEG);
}

#else

static void SPI_WriteByte(uint8_t data) {
    SSP2BUF = data;
    while (!SSP2STATbits.BF);
    (void)SSP2BUF;
}

void MBI_Init(void) {
    ADCON1 = 0x0F;
    CMCON = 0x07;

    TRIS_MBI_OE = 0;
    TRIS_MBI_LE0 = 0; TRIS_MBI_LE1 = 0; TRIS_MBI_LE2 = 0;
    TRIS_MBI_LE3 = 0; TRIS_MBI_LE4 = 0; TRIS_MBI_LE5 = 0;
    
    TRIS_SPI_SCK = 0;
    TRIS_SPI_SDO = 0;

    MBI_OE_PIN = 1;

    MBI_LE0_PIN = 0; MBI_LE1_PIN = 0; MBI_LE2_PIN = 0;
    MBI_LE3_PIN = 0; MBI_LE4_PIN = 0; MBI_LE5_PIN = 0;

    SSP2CON1 = 0x20;
    SSP2STAT = 0x40;

    MBI_ClearAll();
    
    MBI_OE_PIN = 0;
}

void MBI_WriteData(const uint8_t *data, uint8_t length, MBI_Latch_t latch) {
    for (int8_t i = length - 1; i >= 0; i--) {
        SPI_WriteByte(data[i]);
    }

    switch (latch) {
        case MBI_LE0_LED32:   MBI_LE0_PIN = 1; __delay_us(2); MBI_LE0_PIN = 0; break;
        case MBI_LE1_LED7SEG: MBI_LE1_PIN = 1; __delay_us(2); MBI_LE1_PIN = 0; break;
        case MBI_LE2_MATRIX:  MBI_LE2_PIN = 1; __delay_us(2); MBI_LE2_PIN = 0; break;
        case MBI_LE3_LCD:     MBI_LE3_PIN = 1; __delay_us(2); MBI_LE3_PIN = 0; break;
        case MBI_LE4_GLCD:    MBI_LE4_PIN = 1; __delay_us(2); MBI_LE4_PIN = 0; break;
        case MBI_LE5_RELAY:   MBI_LE5_PIN = 1; __delay_us(2); MBI_LE5_PIN = 0; break;
    }
}

void MBI_ClearAll(void) {
    uint8_t buf_00[8] = {0};

    MBI_WriteData(buf_00, 4, MBI_LE0_LED32);
    MBI_WriteData(buf_00, 8, MBI_LE1_LED7SEG);
    MBI_WriteData(buf_00, 4, MBI_LE2_MATRIX);
    MBI_WriteData(buf_00, 2, MBI_LE3_LCD);
    MBI_WriteData(buf_00, 2, MBI_LE4_GLCD);
    MBI_WriteData(buf_00, 2, MBI_LE5_RELAY);
}

#endif
