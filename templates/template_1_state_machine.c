#include "all.h"

typedef enum {
    ST_RUN = 0,
    ST_SET
} app_state_t;

app_state_t state = ST_RUN;
uint32_t limit = 100;
uint32_t buffer = 0;

int main(void) {
    Easy_System_Init();

    while(1) {
        Easy_System_Run();
        uint8_t key = Easy_Keypad_GetKey();

        if (state == ST_RUN) {
            Easy_LCD_PrintFormat(0, 0, "RUN LIMIT: %04ld", limit);
            Easy_LED7_PrintNum(limit);

            if (Easy_Button_IsClicked(0)) {
                state = ST_SET;
                buffer = limit;
                Easy_LCD_ClearLine(0);
            }
        } 
        else if (state == ST_SET) {
            if (Easy_System_GetBlink(300)) {
                Easy_LCD_PrintFormat(0, 0, "SET LIMIT: %04ld", buffer);
                Easy_LED7_PrintNum(buffer);
            } else {
                Easy_LCD_PrintString(0, 0, "SET LIMIT:     ");
                Easy_LED7_PrintString("        ");
            }

            if (key >= 1 && key <= 9) buffer = buffer * 10 + key;
            if (key == 10) buffer = buffer * 10;
            if (key == 11) buffer = 0;

            if (Easy_Button_IsClicked(1)) buffer++;
            if (Easy_Button_IsClicked(2) && buffer > 0) buffer--;

            if (Easy_Button_IsClicked(0)) {
                limit = buffer;
                state = ST_RUN;
                Easy_LCD_ClearLine(0);
                Easy_LED7_StopScroll();
            }
        }
    }
    return 0;
}
