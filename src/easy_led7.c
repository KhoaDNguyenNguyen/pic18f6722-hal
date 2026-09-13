#include "easy_led7.h"
#include "all.h"

static const uint8_t LED7_ASCII_MAP[] = {
    0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x02,
    0x39, 0x0F, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00,
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F, 0x00, 0x00, 0x00, 0x48, 0x00, 0x53,
    0x00, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D,
    0x76, 0x30, 0x1E, 0x7A, 0x38, 0x15, 0x37, 0x3F,
    0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x1C, 0x2A,
    0x76, 0x6E, 0x5B
};

static char led7_scroll_buf[64];
static int16_t led7_scroll_len = 0;
static uint32_t led7_interval = 0;
static uint8_t led7_dir = 0;
static uint32_t led7_last = 0;
static int16_t led7_offset = 0;
static bool led7_scrolling = false;
static uint8_t led7_static_data[8] = {0,0,0,0,0,0,0,0};

static uint8_t CharToHex(char c) {
    if (c >= 'a' && c <= 'z') c -= 32;
    if (c >= ' ' && c <= 'Z') return LED7_ASCII_MAP[c - ' '];
    return 0x00;
}

static void SendToMBI(uint8_t* hex_data) {
    MBI_WriteData(hex_data, 8, MBI_LE1_LED7SEG);
}

void Easy_LED7_PrintNum(int32_t val) {
    led7_scrolling = false;
    LED7_DisplayInt(val);
    LED7_Update();
}

void Easy_LED7_PrintString(const char* str) {
    led7_scrolling = false;
    for (uint8_t i = 0; i < 8; i++) led7_static_data[i] = 0;
    
    uint8_t len = 0;
    while (str[len] && len < 8) len++;
    
    for (uint8_t i = 0; i < len; i++) {
        led7_static_data[len - 1 - i] = CharToHex(str[i]);
    }
    SendToMBI(led7_static_data);
}

void Easy_LED7_SetChar(uint8_t pos, char c) {
    if (pos > 7) return;
    led7_scrolling = false;
    led7_static_data[pos] = CharToHex(c);
    SendToMBI(led7_static_data);
}

void Easy_LED7_Scroll(const char* str, uint32_t interval_ms, uint8_t direction) {
    led7_scroll_len = 0;
    while (*str && led7_scroll_len < 63) {
        led7_scroll_buf[led7_scroll_len++] = *str++;
    }
    led7_interval = interval_ms;
    led7_dir = direction;
    led7_offset = (direction == 0) ? -8 : led7_scroll_len;
    led7_last = Timer_GetMillis();
    led7_scrolling = true;
}

void Easy_LED7_StopScroll(void) {
    led7_scrolling = false;
    for (uint8_t i = 0; i < 8; i++) led7_static_data[i] = 0;
    SendToMBI(led7_static_data);
}

void Easy_LED7_Task(void) {
    if (!led7_scrolling) return;
    uint32_t now = Timer_GetMillis();
    if (now - led7_last >= led7_interval) {
        led7_last = now;
        uint8_t hex_temp[8];
        for (int16_t i = 0; i < 8; i++) {
            int16_t idx = led7_offset + i;
            if (idx >= 0 && idx < led7_scroll_len) {
                hex_temp[7 - i] = CharToHex(led7_scroll_buf[idx]);
            } else {
                hex_temp[7 - i] = 0x00;
            }
        }
        SendToMBI(hex_temp);
        if (led7_dir == 0) {
            led7_offset++;
            if (led7_offset > led7_scroll_len) led7_offset = -8;
        } else {
            led7_offset--;
            if (led7_offset < -8) led7_offset = led7_scroll_len;
        }
    }
}
