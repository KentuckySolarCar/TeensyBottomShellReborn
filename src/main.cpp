#include "common.h"
#include "light.h"

// Initalize CAN ports. See can_setup.h for more info.
typedef FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can0;
typedef FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;
can0 MainCan;
can1 MotorCan;

void main_setup(){
    lightSetup();
}

void setup(){
    chBegin(main_setup);
}

void loop(){
}
