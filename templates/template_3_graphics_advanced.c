#include "all.h"

const uint8_t custom_heart[8] = {
    0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00
};

int main(void) {
    Easy_System_Init();
    
    Easy_LCD_CreateChar(0, custom_heart);

    Easy_LED32_EnableBlink(31, 100);
    Easy_LED32_EnableBlink(0, 500);

    Easy_Matrix_Scroll("10D", 1, 200, 0);

    while(1) {
        Easy_System_Run();

        Easy_LCD_PrintString(0, 0, "TESTING CHAR: ");
        LCD_Command(0x80 + 15);
        LCD_Data(0);

        if (Easy_Button_IsClicked(0)) {
            Easy_LED7_Scroll("SUCCESS", 300, 0);
        }
        
        if (Easy_Button_IsClicked(1)) {
            Easy_LED7_StopScroll();
        }
    }
    return 0;
}
