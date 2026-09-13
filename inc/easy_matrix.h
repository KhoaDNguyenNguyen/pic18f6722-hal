#ifndef EASY_MATRIX_H
#define EASY_MATRIX_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Prints a static string to the LED Matrix.
 *
 * @param str The string to display (max 4-5 characters will fit).
 * @param color 1 (Red), 2 (Green), 3 (Orange/Yellow).
 */
void Easy_Matrix_Print(const char* str, uint8_t color);

/**
 * @brief Scrolls a string automatically across the LED Matrix.
 *
 * @param str The string to scroll.
 * @param color 1 (Red), 2 (Green), 3 (Orange/Yellow).
 * @param interval_ms The speed of scrolling in milliseconds.
 * @param direction 0 for RIGHT to LEFT. 1 for LEFT to RIGHT.
 */
void Easy_Matrix_Scroll(const char* str, uint8_t color, uint32_t interval_ms, uint8_t direction);

/**
 * @brief Stops the scrolling animation and clears the matrix.
 */
void Easy_Matrix_StopScroll(void);

/**
 * @brief Internal task to handle Matrix animations. Do not call directly.
 */
void Easy_Matrix_Task(void);

#endif
