#ifndef EASY_LED7_H
#define EASY_LED7_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Prints an integer directly to the 7-segment display.
 *
 * @param val The integer value to display.
 */
void Easy_LED7_PrintNum(int32_t val);

/**
 * @brief Prints a string directly to the 7-segment display.
 *
 * Only uppercase letters (A-Z), numbers (0-9), and spaces are supported.
 * If the string is longer than 8 characters, it will be truncated.
 *
 * @param str The string to print.
 */
void Easy_LED7_PrintString(const char* str);

/**
 * @brief Sets a specific character at a specific position.
 *
 * @param pos The position. 0 is the RIGHTMOST digit. 7 is the LEFTMOST digit.
 * @param c The character to display (e.g., 'A', '5', ' ').
 */
void Easy_LED7_SetChar(uint8_t pos, char c);

/**
 * @brief Scrolls a string automatically across the 7-segment display.
 *
 * @param str The string to scroll.
 * @param interval_ms The speed of scrolling in milliseconds.
 * @param direction 0 for RIGHT to LEFT. 1 for LEFT to RIGHT.
 */
void Easy_LED7_Scroll(const char* str, uint32_t interval_ms, uint8_t direction);

/**
 * @brief Stops the scrolling animation and clears the display.
 */
void Easy_LED7_StopScroll(void);

/**
 * @brief Internal task to handle LED7 animations. Do not call directly.
 */
void Easy_LED7_Task(void);

#endif
