#ifndef MBI5026_H
#define MBI5026_H

#include "config.h"
#include "hardware.h"
#include <stdint.h>

typedef enum {
    MBI_LE0_LED32   = 0,
    MBI_LE1_LED7SEG = 1,
    MBI_LE2_MATRIX  = 2,
    MBI_LE3_LCD     = 3,
    MBI_LE4_GLCD    = 4,
    MBI_LE5_RELAY   = 5
} MBI_Latch_t;

void MBI_Init(void);
void MBI_WriteData(const uint8_t *data, uint8_t length, MBI_Latch_t latch);
void MBI_ClearAll(void);

#endif
