#warning "EASY_INPUT: Edge-triggered Global Debounce is ENABLED for Keypad & Buttons."
#ifndef EASY_INPUT_H
#define EASY_INPUT_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Checks if a specific button is clicked and released (Debounced).
 *
 * @param btn_id Button ID from 0 to 3.
 * @return true if the button was clicked, false otherwise.
 */
bool Easy_Button_IsClicked(uint8_t btn_id);

/**
 * @brief Checks if a specific button is being held down.
 *
 * @param btn_id Button ID from 0 to 3.
 * @return true if the button is currently held down, false otherwise.
 */
bool Easy_Button_IsHeld(uint8_t btn_id);

/**
 * @brief Reads the current pressed key from the 4x4 Keypad.
 *
 * @return Key ID from 1 to 16. Returns 0 if no key is pressed.
 */
uint8_t Easy_Keypad_GetKey(void);

/**
 * @brief Reads the current accumulated value of the Rotary Encoder.
 *
 * Rotating clockwise increases the value. Rotating counter-clockwise decreases it.
 *
 * @return The current integer value.
 */
int32_t Easy_Encoder_GetValue(void);

#endif
