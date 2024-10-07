#ifndef LIGHT_H
#define LIGHT_H

#include "common.h"

// the following was pulled from TeensyBottomShell
#define HEADLIGHTS_BRIGHTNESS   120
#define BRAKES_BRIGHTNESS       80
#define TURN_SIGNALS_BRIGHTNESS 80
#define TURN_SIGNALS_SPEED      500
#define TEST_LIGHT_SPEED      500

extern bool isThrottleUnlocked;
extern bool isBrakePressed;

// Uncomment if we want to expose lightState publicly
/*
extern struct {
    bool isLeftTurnOn = false;
    bool isRightTurnOn = false;
    bool isStrobeOn = false;
    bool isHeadlightOn = false;
    bool isBrakeOn = false;
    bool isLightTestOn = false;
    bool isThrottleUnlocked = false;
    bool isBrakePressed = false;
} lightState;
*/

/**
 * @brief Function called in the "setup" phase. Initializes light threads and establishes light state.
 * Combination of `lightSetup` and `routerSetup` from TBS.
 * @param msg Input CAN message. Assumes correct ID and layout.
 */
void lightSetup();

/**
 * @brief Function to update left light state based on an inputted can message. Assumes correct ID.
 * @param msg Input CAN message. Assumes correct ID and layout.
 */
void updateLeftLight(CAN_message_t msg);
/**
 * @brief Function to update right light state based on an inputted can message. Assumes correct ID.
 * @param msg Input CAN message. Assumes correct ID and layout.
 */
void updateRightLight(CAN_message_t msg);

/**
 * @brief Function to update headlight state based on an inputted can message. Assumes correct ID.
 * @param msg Input CAN message. Assumes correct ID and layout.
 */
void updateHeadlights(CAN_message_t msg);
/**
 * @brief Function to update brake lights based on an already parsed can message. Called in response to a change in the brakes.
 * @param msg Input CAN message. Assumes correct ID and layout.
 */
void updateBrakeLights(bool msg);

/**
 * @brief Function to update the battery protection system light. If something goes VERY wrong with the batteries, we tigger a light indicating so.
 * @param msg Input CAN message. Assumes correct ID and layout.
 */
void updateBPSLight(CAN_message_t msg);

/**
 * @brief
 */
void updateYButtonLong(CAN_message_t msg);

/**
 * @brief Function to blink BPS lights. Called if bad things happen to the battery.
 */
void handleBPSLight(void);

#endif // LIGHT_H
