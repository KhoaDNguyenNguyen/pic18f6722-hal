#include "rotary_encoder.h"
#include "hardware.h"

static int32_t encoder_value = 0;
static uint8_t last_state = 0;

void RotaryEncoder_Init(void) {
    TRIS_ENC_A = 1;
    TRIS_ENC_B = 1;
    last_state = 0;
}

void RotaryEncoder_Update(void) {
    uint8_t vt_ht = 0;
    if(ENC_A_PIN == 0 && ENC_B_PIN == 0) vt_ht = 0;
    else if(ENC_A_PIN == 1 && ENC_B_PIN == 0) vt_ht = 1;
    else if(ENC_A_PIN == 1 && ENC_B_PIN == 1) vt_ht = 2;
    else if(ENC_A_PIN == 0 && ENC_B_PIN == 1) vt_ht = 3;
    
    if(last_state == 0) {
        if(vt_ht == 1) encoder_value++;
        else if(vt_ht == 3) encoder_value--;
    }
    else if(last_state == 1) {
        if(vt_ht == 2) encoder_value++;
        else if(vt_ht == 0) encoder_value--;
    }
    else if(last_state == 2) {
        if(vt_ht == 3) encoder_value++;
        else if(vt_ht == 1) encoder_value--;
    }
    else if(last_state == 3) {
        if(vt_ht == 0) encoder_value++;
        else if(vt_ht == 2) encoder_value--;
    }
    last_state = vt_ht;
}

int32_t RotaryEncoder_GetValue(void) {
    return encoder_value >> 2;
}
