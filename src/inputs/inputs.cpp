#include "inputs.h"

struct {
    // true if from wheel, false if from panel
    bool fromWheel;
    // true if forward, false if backward
    bool wheelForward;
    // true if brake switch is set
    bool brakeSwitch;
    // if you're in cruise control and this flag is set, regen breaking will keep you at cruise
    // speed if you're going down a hill
    // true if cruise regen is enabled
    bool cruiseRegen;
} switchBoard;

bool getForwardReverse() {
    if (switchBoard.fromWheel) {
        return digitalRead(FORWARD_REVERSE_IN) == 1;
    } else {
        return switchBoard.wheelForward;
    }
}

inline bool getBrakeSwitch() {
    switchBoard.brakeSwitch = digitalRead(BRAKE_SWITCH);
    return switchBoard.brakeSwitch;
}

inline bool getCruiseRegen() {
    return switchBoard.cruiseRegen;
}

inline bool isWheel() {
    return switchBoard.fromWheel;
}

inline void handleWheelOrPanel(CAN_message_t msg) {
    switchBoard.fromWheel = (parseCANBuf<short, 0>(msg) % 2) == 0;
}

inline void handleWheelForRev(CAN_message_t msg) {
    switchBoard.wheelForward = (parseCANBuf<short, 0>(msg) % 2) == 0;
}

inline void handleCruiseRegen(CAN_message_t msg) {
    switchBoard.cruiseRegen = (parseCANBuf<short, 1>(msg) % 2) != 0;
}