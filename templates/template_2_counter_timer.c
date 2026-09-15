#include "all.h"

uint32_t products = 0;
uint32_t start_time = 0;
bool is_active = false;

int main(void) {
    Easy_System_Init();

    while(1) {
        Easy_System_Run();
        products = Counter_Get();

        Easy_LCD_PrintFormat(0, 0, "PROD: %04ld", products);
        Easy_GLCD_PrintFormat(0, 0, "PROD: %04ld", products);

        if (Easy_Button_IsClicked(0)) {
            Counter_Reset();
        }

        if (Easy_Button_IsClicked(1)) {
            Easy_Buzzer_Set(true);
            is_active = true;
            start_time = Timer_GetMillis();
        }

        if (is_active && (Timer_GetMillis() - start_time >= 3000)) {
            Easy_Buzzer_Set(false);
            is_active = false;
        }

        if (tmr3_1s_flag) {
            Timer3_ClearFlag();
            Easy_LED32_Toggle(0);
        }
    }
    return 0;
}
