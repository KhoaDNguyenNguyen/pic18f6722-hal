#include "buzzer.h"
#include "mbi5026.h"
#include "hardware.h"

static uint16_t actuator_reg = 0;

static void Actuator_Update(void) {
#ifdef TARGET_SIMULATION
    BUZZER_PIN = (actuator_reg & (1U << 13)) ? 1 : 0;
    RELAY_PIN = (actuator_reg & (1U << 14)) ? 1 : 0;
#else
    uint8_t data[2];
    data[0] = (uint8_t)(actuator_reg & 0xFF);
    data[1] = (uint8_t)((actuator_reg >> 8) & 0xFF);
    MBI_WriteData(data, 2, MBI_LE5_RELAY);
#endif
}

static void Actuator_SetBit(uint8_t bit_pos, bool state) {
    if (state) actuator_reg |= (1U << bit_pos);
    else       actuator_reg &= ~(1U << bit_pos);
    Actuator_Update();
}

void Buzzer_Init(void) {
#ifdef TARGET_SIMULATION
    TRIS_BUZZER = 0;
    TRIS_RELAY = 0;
    BUZZER_PIN = 0;
    RELAY_PIN = 0;
#endif
    actuator_reg = 0;
    Actuator_Update();
}

void Triac1_Set(bool state) { Actuator_SetBit(11, state); }
void Triac2_Set(bool state) { Actuator_SetBit(12, state); }
void Buzzer_Set(bool state) { Actuator_SetBit(13, state); }
void Relay1_Set(bool state) { Actuator_SetBit(14, state); }
void Relay2_Set(bool state) { Actuator_SetBit(15, state); }
