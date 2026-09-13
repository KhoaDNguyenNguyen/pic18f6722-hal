#ifndef EASY_LED32_H
#define EASY_LED32_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Turns a specific LED on or off directly.
 *
 * @param pos The position of the LED. 0 is the RIGHTMOST (LSB). 31 is the LEFTMOST (MSB).
 * @param state Set to true to turn ON, false to turn OFF.
 */
void Easy_LED32_Set(uint8_t pos, bool state);

/**
 * @brief Toggles the current state of a specific LED.
 *
 * @param pos The position of the LED. 0 is the RIGHTMOST (LSB). 31 is the LEFTMOST (MSB).
 */
void Easy_LED32_Toggle(uint8_t pos);

/**
 * @brief Enables automatic blinking for a specific LED.
 *
 * The blinking happens in the background. Ensure Easy_System_Run() is in your while(1) loop.
 *
 * @param pos The position of the LED. 0 is the RIGHTMOST (LSB). 31 is the LEFTMOST (MSB).
 * @param interval_ms The blinking speed in milliseconds (e.g., 500 for half a second).
 */
void Easy_LED32_EnableBlink(uint8_t pos, uint32_t interval_ms);

/**
 * @brief Disables automatic blinking for a specific LED and turns it off.
 *
 * @param pos The position of the LED. 0 is the RIGHTMOST (LSB). 31 is the LEFTMOST (MSB).
 */
void Easy_LED32_DisableBlink(uint8_t pos);

/**
 * @brief Internal task to handle LED blinking. Do not call directly.
 */
void Easy_LED32_Task(void);

#endif
