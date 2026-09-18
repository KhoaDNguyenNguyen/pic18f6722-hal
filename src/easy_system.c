#include "easy_system.h"
#include "easy_led32.h"
#include "easy_led7.h"
#include "easy_matrix.h"
#include "all.h"

void Easy_System_Init(void) {
    MBI_Init();
    Buzzer_Init();
    LCD_Init();
    GLCD_Init();
    Button_Init();
    Timer_Init();
    Counter_Init();
    Keypad_Init();
    LED7_Init();
    LED32_Init();
    LEDMatrix_Init();
    RotaryEncoder_Init();
    Easy_RTC_Init();
}

void Easy_System_Run(void) {
    LEDMatrix_Scan();
    Easy_LED32_Task();
    Easy_LED7_Task();
    Easy_Matrix_Task();
}
