#include "light.h"

// VERY TEMPORARY STUFF FOR ERROR'S SAKE
#define CAN_BPS_STATUS 0
#define CAN_BUTTON_LEFT_TURN 1
#define CAN_BUTTON_RIGHT_TURN 2
#define CAN_BUTTON_HEADLIGHTS 3
#define CAN_BUTTON_Y 4

// the setup of this code is as follows:
// we define two threads, one for routing can messages, and the other for updating the blinking of the lights.
// the can router updates our internal state for the lights, while the blinker reflects this on the physical system.

struct {
    bool isLeftTurnOn = false;
    bool isRightTurnOn = false;
    bool isStrobeOn = false;
    bool isHeadlightOn = false;
    bool isBrakeOn = false;
    bool isLightTestOn = false;
} lightState;

// Explanation of THD_WORKING_AREA:
// the first parameter to this macro is the name of the data.
// the second parameter is the size of the data we're working with. In this case, 4096 bytes.
// we then define a function that operates in a thread called in the setup function.
static THD_WORKING_AREA(wa_light_route, LIGHTS_WA);
static THD_FUNCTION(light_route_thd, arg) {
    (void) arg;

    CAN_message_t msg;
    while (true) {
        while (MainCan.read(msg)) {
            switch (msg.id) {
                case CAN_BPS_STATUS: updateBPSLight(msg); break;
                case CAN_BUTTON_LEFT_TURN: updateLeftLight(msg); break;
                case CAN_BUTTON_RIGHT_TURN: updateRightLight(msg); break;
                case CAN_BUTTON_HEADLIGHTS: updateHeadlights(msg); break;
                case CAN_BUTTON_Y: updateYButtonLong(msg); break;
                default: {
                    // we'll figure out alert messages later
                    break;
                }
            }
        }

        /* TODO: Uncomment when isBrakePressed is implemented
        if (isBrakePressed) {
            updateBrakeLights(isBrakePressed);
        }
        */

        handleBPSLight();
        chThdSleepMilliseconds(ROUTER_SLEEP);
    }
}

static THD_WORKING_AREA(wa_light_blink, LIGHTS_WA);
static THD_FUNCTION(light_blink_thd, arg) {
    // prevent compiler for complaining about unused stuff
    (void) arg;

    uint32_t blinkTimer = millis();
    bool isOn = false;
    while (true) {
        // change light status
        if (!lightState.isLeftTurnOn && !lightState.isRightTurnOn) {
            isOn = false;
            digitalWrite(LT_CTRL, LOW);
            digitalWrite(RT_CTRL, LOW);
        } else if (millis() - blinkTimer > TURN_SIGNALS_SPEED) {
            blinkTimer = millis();
            isOn = !isOn;
            digitalWrite(LT_CTRL, isOn && lightState.isLeftTurnOn);
            digitalWrite(RT_CTRL, isOn && lightState.isRightTurnOn);
        }

        digitalWrite(RUNNING_LIGHTS, lightState.isHeadlightOn);
        digitalWrite(BRAKE_CTRL, lightState.isBrakeOn);

        /* TODO: Uncomment when isThrottleUnlocked is implemented
        if (lightState.isLightTestOn && isThrottleUnlocked) {
            if (millis() - blinkTimer > TURN_SIGNALS_BRIGHTNESS) {
                blinkTimer = millis();
                isOn = !isOn;
                digitalWrite(LT_CTRL,  isOn);
                digitalWrite(RT_CTRL, isOn);
                digitalWrite(BRAKE_CTRL, isOn);
                digitalWrite(RUNNING_LIGHTS, isOn);
                digitalWrite(BPS_STROBE, isOn);
            }
        }
        */

        chThdSleepMilliseconds(LIGHTS_SLEEP);
    }
}

void lightSetup() {
    pinMode(BPS_STROBE,OUTPUT);
    pinMode(LT_CTRL,OUTPUT);
    pinMode(RT_CTRL,OUTPUT);
    pinMode(RUNNING_LIGHTS,OUTPUT);
    pinMode(BRAKE_CTRL,OUTPUT);

    digitalWrite(BPS_STROBE, LOW);

    chThdCreateStatic(wa_light_route, sizeof(wa_light_route), ROUTER_PRIO, light_route_thd, NULL);
    chThdCreateStatic(wa_light_blink, sizeof(wa_light_blink), LIGHTS_PRIO, light_blink_thd, NULL);
}

void updateLeftLight(CAN_message_t ltMsg){
    lightState.isLeftTurnOn = ltMsg.buf[0] % 2;
}

void updateRightLight(CAN_message_t rtMsg){
    lightState.isRightTurnOn = rtMsg.buf[0] % 2;
}

void updateHeadlights(CAN_message_t lightMsg){
    lightState.isHeadlightOn = lightMsg.buf[0] % 2;
}

void updateBrakeLights(bool brakeMsg){
    lightState.isBrakeOn = brakeMsg;
}

void updateBPSLight(CAN_message_t statusMsg){
    lightState.isStrobeOn = statusMsg.buf[1]; // This is 1(TRUE) if the battery pack is terminated by a fault, or 0(FALSE) if conditions are safe
}

void updateYButtonLong(CAN_message_t lightTestMsg){
    lightState.isLightTestOn = lightTestMsg.buf[2] % 2;
}


void handleBPSLight(){
    static uint32_t timer = millis();
    static bool isOn = false;

    if (lightState.isStrobeOn){
        if ((millis() - timer) > TURN_SIGNALS_SPEED){
            timer = millis();
            isOn = !isOn;
            digitalWrite(BPS_STROBE,isOn);
        }
    } else {
        isOn = false;
        digitalWrite(BPS_STROBE, isOn);
    }
}
