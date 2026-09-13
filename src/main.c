#include "all.h"

int main(void) {
    Easy_System_Init(); 


    while(1) {
    
        Easy_System_Run();
        uint8_t key = Easy_Keypad_GetKey();
        Easy_LCD_PrintFormat(0, 0, "key: %d is pressed", key);
        Easy_GLCD_PrintFormat(0, 0, "key: %d is pressed", key);
        Easy_LED7_PrintNum(key);
        for(int i = 0; i<key; i++) Easy_LED32_EnableBlink(key, 1000);
        Easy_Matrix_Print("key", 1);

    }
    return 0;
}