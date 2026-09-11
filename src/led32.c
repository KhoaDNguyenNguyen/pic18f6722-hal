#include "led32.h"
#include "mbi5026.h"

void LED32_Init(void) {
    LED32_SetState(0x00000000);
}

void LED32_SetState(uint32_t state) {
    uint8_t data[4];
    data[0] = state & 0xFF;
    data[1] = (state >> 8) & 0xFF;
    data[2] = (state >> 16) & 0xFF;
    data[3] = (state >> 24) & 0xFF;
    MBI_WriteData(data, 4, MBI_LE0_LED32);
}
