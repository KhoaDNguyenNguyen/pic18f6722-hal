#include "button.h"
#include "hardware.h"
#include "config.h"

void Button_Init(void) {
    TRIS_BT0 = 1;
    TRIS_BT1 = 1;
    TRIS_BT2 = 1;
    TRIS_BT3 = 1;
}

bool Button_GetState(Button_t btn) {
    switch (btn) {
        case BTN_0: return (BT0_PIN == 0);
        case BTN_1: return (BT1_PIN == 0);
        case BTN_2: return (BT2_PIN == 0);
        case BTN_3: return (BT3_PIN == 0);
        default: return 0;
    }
}

bool Button_SingleClick(Button_t btn) {
    if (Button_GetState(btn)) {
        __delay_ms(20);
        if (Button_GetState(btn)) {
            while (Button_GetState(btn));
            return 1;
        }
    }
    return 0;
}

bool Button_PressHold(Button_t btn) {
    if (Button_GetState(btn)) {
        __delay_ms(20);
        if (Button_GetState(btn)) {
            __delay_ms(150);
            return 1;
        }
    }
    return 0;
}
