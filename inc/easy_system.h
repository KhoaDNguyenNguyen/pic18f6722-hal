#ifndef EASY_SYSTEM_H
#define EASY_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initializes the entire hardware system and all easy modules.
 *
 * You only need to call this single function at the very beginning of your main() function.
 * It automatically sets up the MBI shift registers, timers, screens, and inputs.
 */
void Easy_System_Init(void);

/**
 * @brief The master task runner for background processes (Blinking, Scrolling, Matrix Scan).
 *
 * You MUST call this function continuously inside your main while(1) loop.
 * It handles the LED matrix scanning and all non-blocking animations automatically.
 */
void Easy_System_Run(void);

bool Easy_System_GetBlink(uint32_t interval_ms);
#endif
