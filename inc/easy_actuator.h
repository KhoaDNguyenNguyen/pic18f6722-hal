#ifndef EASY_ACTUATOR_H
#define EASY_ACTUATOR_H

#include <stdbool.h>

/**
 * @brief Controls the buzzer.
 * @param state true (ON) or false (OFF).
 */
void Easy_Buzzer_Set(bool state);

/**
 * @brief Controls Relay 1.
 * @param state true (ON) or false (OFF).
 */
void Easy_Relay1_Set(bool state);

/**
 * @brief Controls Relay 2.
 * @param state true (ON) or false (OFF).
 */
void Easy_Relay2_Set(bool state);

/**
 * @brief Controls Triac 1.
 * @param state true (ON) or false (OFF).
 */
void Easy_Triac1_Set(bool state);

/**
 * @brief Controls Triac 2.
 * @param state true (ON) or false (OFF).
 */
void Easy_Triac2_Set(bool state);

#endif
