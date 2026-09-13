#include "easy_led32.h"
#include "all.h"

static uint32_t led32_state = 0;
static uint32_t led32_blink_mask = 0;
static uint32_t led32_intervals[32];
static uint32_t led32_last_ticks[32];

void Easy_LED32_Set(uint8_t pos, bool state) {
    if (pos > 31) return;
    led32_blink_mask &= ~(1UL << pos);
    if (state) led32_state |= (1UL << pos);
    else led32_state &= ~(1UL << pos);
    LED32_SetState(led32_state);
}

void Easy_LED32_Toggle(uint8_t pos) {
    if (pos > 31) return;
    led32_blink_mask &= ~(1UL << pos);
    led32_state ^= (1UL << pos);
    LED32_SetState(led32_state);
}

void Easy_LED32_EnableBlink(uint8_t pos, uint32_t interval_ms) {
    if (pos > 31) return;
    led32_blink_mask |= (1UL << pos);
    led32_intervals[pos] = interval_ms;
    led32_last_ticks[pos] = Timer_GetMillis();
}

void Easy_LED32_DisableBlink(uint8_t pos) {
    if (pos > 31) return;
    led32_blink_mask &= ~(1UL << pos);
    led32_state &= ~(1UL << pos);
    LED32_SetState(led32_state);
}

void Easy_LED32_Task(void) {
    if (!led32_blink_mask) return;
    uint32_t now = Timer_GetMillis();
    bool changed = false;
    for (uint8_t i = 0; i < 32; i++) {
        if (led32_blink_mask & (1UL << i)) {
            if (now - led32_last_ticks[i] >= led32_intervals[i]) {
                led32_last_ticks[i] = now;
                led32_state ^= (1UL << i);
                changed = true;
            }
        }
    }
    if (changed) LED32_SetState(led32_state);
}
