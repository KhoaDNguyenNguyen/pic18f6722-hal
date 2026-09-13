#include "easy_input.h"
#include "all.h"

bool Easy_Button_IsClicked(uint8_t btn_id) {
    switch (btn_id) {
        case 0: return Button_SingleClick(BTN_0);
        case 1: return Button_SingleClick(BTN_1);
        case 2: return Button_SingleClick(BTN_2);
        case 3: return Button_SingleClick(BTN_3);
        default: return false;
    }
}

bool Easy_Button_IsHeld(uint8_t btn_id) {
    switch (btn_id) {
        case 0: return Button_PressHold(BTN_0);
        case 1: return Button_PressHold(BTN_1);
        case 2: return Button_PressHold(BTN_2);
        case 3: return Button_PressHold(BTN_3);
        default: return false;
    }
}

uint8_t Easy_Keypad_GetKey(void) {
    return Keypad_ReadSingle();
}

int32_t Easy_Encoder_GetValue(void) {
    return RotaryEncoder_GetValue();
}
