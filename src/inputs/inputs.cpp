#include "inputs.h"
#include "can_msg_ids.h"

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

void handleCANData(const CAN_message_t &msg) {
    switch (msg.id) {
        case CAN_BUTTON_R: { handleWheelOrPanel(msg); break; }
        case CAN_BUTTON_B: { handleWheelForRev(msg); break; }
        case CAN_BUTTON_X: { handleCruiseRegen(msg); break; }
        default: { /*error?*/ }
    }
}

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

inline void handleWheelOrPanel(const CAN_message_t &msg) {
    switchBoard.fromWheel = (parseCANBuf<short, 0>(msg) % 2) == 0;
}

inline void handleWheelForRev(const CAN_message_t &msg) {
    switchBoard.wheelForward = (parseCANBuf<short, 0>(msg) % 2) == 0;
}

inline void handleCruiseRegen(const CAN_message_t &msg) {
    switchBoard.cruiseRegen = (parseCANBuf<short, 1>(msg) % 2) != 0;
}