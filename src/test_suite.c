#include "all.h"

void Test_RunAll(void) {
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Print("SYS TEST BOOT");

    GLCD_Clear();
    GLCD_SetCursor(0, 0);
    GLCD_Print("SYS TEST BOOT");

    LED32_SetState(0xFFFFFFFF);
    LED7_DisplayInt(88888888);
    LED7_Update();
    LEDMatrix_Print("RDY", 3);

    uint32_t start = Timer_GetMillis();
    while (Timer_GetMillis() - start < 1000) {
        LEDMatrix_Scan();
    }

    LED32_SetState(0x00000000);
    LED7_Clear();
    LED7_Update();
    LEDMatrix_Clear();
}

void Test_Interactive(void) {
    LCD_Clear();
    GLCD_Clear();
    
    uint32_t last_lcd = 0;
    uint8_t current_disp = 255;
    
    while(1) {
        LEDMatrix_Scan();
        
        uint32_t now = Timer_GetMillis();
        if (now - last_lcd >= 50) {
            last_lcd = now;
            
            int32_t enc = RotaryEncoder_GetValue();
            uint8_t key = Keypad_ReadSingle();
            
            uint8_t b0 = Button_GetState(BTN_0);
            uint8_t b1 = Button_GetState(BTN_1);
            uint8_t b2 = Button_GetState(BTN_2);
            uint8_t b3 = Button_GetState(BTN_3);
            
            uint8_t new_disp = 0;
            
            if (key != 0) {
                new_disp = 100 + key;
            } else if (b0) {
                new_disp = 1;
            } else if (b1) {
                new_disp = 2;
            } else if (b2) {
                new_disp = 3;
            } else if (b3) {
                new_disp = 4;
            } else {
                new_disp = 0;
            }
            
            if (new_disp != current_disp) {
                current_disp = new_disp;
                
                if (current_disp > 100) {
                    uint8_t k = current_disp - 100;
                    LED7_DisplayInt(k);
                    char mbuf[8];
                    mbuf[0] = 'K'; 
                    mbuf[1] = ' ';
                    if (k >= 10) {
                        mbuf[2] = (char)((k / 10) + '0');
                        mbuf[3] = (char)((k % 10) + '0');
                        mbuf[4] = 0;
                    } else {
                        mbuf[2] = (char)(k + '0');
                        mbuf[3] = 0;
                    }
                    LEDMatrix_Print(mbuf, 1);
                } else if (current_disp == 1) {
                    LED7_DisplayInt(0);
                    LEDMatrix_Print("BTN0", 2);
                } else if (current_disp == 2) {
                    LED7_DisplayInt(1);
                    LEDMatrix_Print("BTN1", 2);
                } else if (current_disp == 3) {
                    LED7_DisplayInt(2);
                    LEDMatrix_Print("BTN2", 2);
                } else if (current_disp == 4) {
                    LED7_DisplayInt(3);
                    LEDMatrix_Print("BTN3", 2);
                } else {
                    LED7_DisplayInt(enc);
                    LEDMatrix_Print("TEST", 3);
                }
                LED7_Update();
            }
            
            if (current_disp == 0) {
                LED7_DisplayInt(enc);
                LED7_Update();
            }
            
            LCD_SetCursor(0, 0); LCD_Print("ENC: "); LCD_PrintInt(enc); LCD_Print("     ");
            LCD_SetCursor(1, 0); LCD_Print("KEY: "); LCD_PrintInt(key); LCD_Print("     ");
            LCD_SetCursor(2, 0); LCD_Print("BTN: ");
            LCD_PrintInt(b3); LCD_PrintInt(b2); LCD_PrintInt(b1); LCD_PrintInt(b0);
            
            GLCD_SetCursor(0, 0); GLCD_Print("ENC: "); GLCD_PrintInt(enc); GLCD_Print("     ");
            GLCD_SetCursor(1, 0); GLCD_Print("KEY: "); GLCD_PrintInt(key); GLCD_Print("     ");
            GLCD_SetCursor(2, 0); GLCD_Print("BTN: ");
            GLCD_PrintInt(b3); GLCD_PrintInt(b2); GLCD_PrintInt(b1); GLCD_PrintInt(b0);
            
            if (b0) Buzzer_Set(1); else Buzzer_Set(0);
            if (b1) Relay1_Set(1); else Relay1_Set(0);
            if (b2) Triac1_Set(1); else Triac1_Set(0);
            if (b3) LED32_SetState(0xFFFFFFFF); else LED32_SetState((uint32_t)enc);
        }
    }
}
