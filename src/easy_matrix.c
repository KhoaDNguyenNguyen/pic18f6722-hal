#include "easy_matrix.h"
#include "all.h"

static char mat_scroll_buf[64];
static int16_t mat_scroll_len = 0;
static uint32_t mat_interval = 0;
static uint8_t mat_dir = 0;
static uint8_t mat_color = 0;
static uint32_t mat_last = 0;
static int16_t mat_offset = 0;
static bool mat_scrolling = false;

void Easy_Matrix_Print(const char* str, uint8_t color) {
    mat_scrolling = false;
    LEDMatrix_Print(str, color);
}

void Easy_Matrix_Scroll(const char* str, uint8_t color, uint32_t interval_ms, uint8_t direction) {
    mat_scroll_len = 0;
    while (*str && mat_scroll_len < 63) {
        mat_scroll_buf[mat_scroll_len++] = *str++;
    }
    mat_color = color;
    mat_interval = interval_ms;
    mat_dir = direction;
    mat_offset = (direction == 0) ? -4 : mat_scroll_len;
    mat_last = Timer_GetMillis();
    mat_scrolling = true;
}

void Easy_Matrix_StopScroll(void) {
    mat_scrolling = false;
    LEDMatrix_Clear();
}

void Easy_Matrix_Task(void) {
    if (!mat_scrolling) return;
    uint32_t now = Timer_GetMillis();
    if (now - mat_last >= mat_interval) {
        mat_last = now;
        char temp[5];
        for (int16_t i = 0; i < 4; i++) {
            int16_t idx = mat_offset + i;
            if (idx >= 0 && idx < mat_scroll_len) {
                temp[i] = mat_scroll_buf[idx];
            } else {
                temp[i] = ' ';
            }
        }
        temp[4] = '\0';
        LEDMatrix_Print(temp, mat_color);
        
        if (mat_dir == 0) {
            mat_offset++;
            if (mat_offset > mat_scroll_len) mat_offset = -4;
        } else {
            mat_offset--;
            if (mat_offset < -4) mat_offset = mat_scroll_len;
        }
    }
}
