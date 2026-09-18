#ifndef EASY_SCREEN_H
#define EASY_SCREEN_H

#include <stdint.h>

/**
 * @brief Prints a string to the LCD 20x4 at a specific coordinate.
 */
void Easy_LCD_PrintString(uint8_t x, uint8_t y, const char* str);

/**
 * @brief Prints an integer to the LCD 20x4 at a specific coordinate.
 */
void Easy_LCD_PrintNum(uint8_t x, uint8_t y, int32_t val);

/**
 * @brief Clears an entire row on the LCD to remove old characters.
 * @param y Row coordinate (0 to 3).
 */
void Easy_LCD_ClearLine(uint8_t y);

/**
 * @brief Prints a formatted string (like printf) to the LCD.
 * @param x Column coordinate.
 * @param y Row coordinate.
 * @param format Format string (e.g., "Temp: %d C").
 */
void Easy_LCD_PrintFormat(uint8_t x, uint8_t y, const char* format, ...);

/**
 * @brief Prints a string to the GLCD 128x64 at a specific coordinate.
 */
void Easy_GLCD_PrintString(uint8_t x, uint8_t y, const char* str);

/**
 * @brief Prints an integer to the GLCD 128x64 at a specific coordinate.
 */
void Easy_GLCD_PrintNum(uint8_t x, uint8_t y, int32_t val);

/**
 * @brief Clears an entire row on the GLCD to remove old characters.
 * @param y Row coordinate (0 to 3).
 */
void Easy_GLCD_ClearLine(uint8_t y);

/**
 * @brief Prints a formatted string (like printf) to the GLCD.
 * @param x Column coordinate.
 * @param y Row coordinate.
 * @param format Format string (e.g., "Val: %d").
 */
void Easy_GLCD_PrintFormat(uint8_t x, uint8_t y, const char* format, ...);

#endif
void Easy_LCD_InitBigNumbers(void);
void Easy_LCD_PrintBigNum(uint8_t x, uint8_t y, uint8_t val);
void Easy_GLCD_GraphicMode(uint8_t enable);
void Easy_GLCD_DrawCheckerboard(void);
