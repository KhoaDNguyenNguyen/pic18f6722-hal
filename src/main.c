#include "all.h"

int main(void) {
    Easy_System_Init();

    Easy_LCD_InitBigNumbers();
    Easy_GLCD_GraphicMode(1);
    Easy_GLCD_DrawCheckerboard();

    int32_t last_enc = -1;

    while(1) {
        Easy_System_Run();

        int32_t current_enc = Easy_Encoder_GetValue();
        if (current_enc < 0) current_enc = 0;
        if (current_enc > 99) current_enc = 99;

        if (current_enc != last_enc) {
            last_enc = current_enc;

            Easy_LCD_ClearLine(0);
            Easy_LCD_ClearLine(1);
            Easy_LCD_PrintFormat(0, 0, "Bignum Test:");

            Easy_LCD_PrintBigNum(0, 2, current_enc / 10);
            Easy_LCD_PrintBigNum(4, 2, current_enc % 10);

            Easy_LED7_PrintNum(current_enc);
        }

        uint8_t key = Easy_Keypad_GetKey();
        if (key) {
            Easy_LCD_PrintFormat(13, 2, "K:%02d", key);
            Easy_Matrix_Print("TEST", 2);
        }
    }
    return 0;
}
