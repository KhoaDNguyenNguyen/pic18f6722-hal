#include "all.h"

int main(void) {
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
    
    Test_RunAll();
    Test_Interactive();

    while(1);
    return 0;
}
