#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    BTN_0 = 0,
    BTN_1 = 1,
    BTN_2 = 2,
    BTN_3 = 3
} Button_t;

void Button_Init(void);
bool Button_GetState(Button_t btn);
bool Button_SingleClick(Button_t btn);
bool Button_PressHold(Button_t btn);

#endif
