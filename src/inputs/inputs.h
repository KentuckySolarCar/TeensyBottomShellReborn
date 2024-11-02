//! Input data that modifies internal state.

#ifndef INPUTS_H
#define INPUTS_u

#include "common.h"

/**
 * @brief Returns whether the brake is currently pressed to any degree.
 */
bool getBrakeSwitch();
/**
 * @brief Returns whether the car is currently moving forwards or backwards. Set from both wheel and panel.
 */
bool getForwardReverse();
/**
 * @brief Returns whether the car is using cruise regen or not.
 * @details Cruise Regen is where a car uses magnetic regen to maintain the speed of the car's cruise
 * control in the event it slows down due to, for example, rolling down a hill.
 */
bool getCruiseRegen();
/**
 * @brief Returns whether the previous CAN message input came from the wheel or the panel.
 */
bool isWheel();

/**
 * @brief Sets internal state to if an input came from the wheel or the panel.
 * @details The internal state is stored privately in the associated implementation file.
 * @param msg CAN message to parse
 * @see isWheel()
 */
void handleWheelOrPanel(const CAN_message_t &msg);
/**
 * @brief Parses a CAN message and updates internal state to whether the car should move forwards or backwards.
 * @details The internal state is stored privately in the associated implementation file.
 * @param msg CAN message to parse
 */
void handleWheelForRev(const CAN_message_t &msg);
/**
 * @brief Parses a CAN message and updates internal state to whether the car should do "cruise regen".
 * @details Cruise Regen is where a car uses magnetic regen to maintain the speed of the car's cruise
 * control in the event it slows down due to, for example, rolling down a hill. The internal state is
 * stored privately in the associated implementation file.
 * @param msg CAN message to parse
 */
void handleCruiseRegen(const CAN_message_t &msg);

#endif