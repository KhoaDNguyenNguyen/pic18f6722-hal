#include "keypad.h"
#include "hardware.h"
#include "config.h"

void Keypad_Init(void) {
#ifndef TARGET_SIMULATION
    TRIS_KP_CK = 0;
    TRIS_KP_DT = 1;
    KP_CK_PIN = 1;
#endif
}

uint8_t Keypad_ReadSingle(void) {
#ifdef TARGET_SIMULATION
    static uint8_t sim_count = 0;
    if(sim_count++ > 30) return 16;
    return 0;
#else
    uint8_t key = 0;
    for (uint8_t i = 1; i <= 16; i++) {
        KP_CK_PIN = 0;
        __delay_us(70);
        if (KP_DT_PIN == 0) key = i;
        KP_CK_PIN = 1;
        __delay_us(70);
    }
    return key;
#endif
}

uint16_t Keypad_ReadMask(void) {
    return 0;
}
