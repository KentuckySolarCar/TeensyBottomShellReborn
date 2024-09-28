/**
 * @file can_setup.h
 * @brief Declares the CAN ports used by the board
 * @version 0.1
 * 
 * This header file must be included in any file that sends or receives data via CAN.
 * Each port object must be instantiated only once, so we instantiate them in
 * main.cpp and declare them here.
 * 
 */

#ifndef CAN_SETUP_H
#define CAN_SETUP_H

#include <FlexCAN_T4.h>

/**
 * These typedefs aren't required, but they let us rename the ports.
 * Note that we're calling CAN1 can0 and we're calling CAN2 can1.
 * This is done to match the labels on the boards.
 */
typedef FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can0;
typedef FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can1;


/**
 * This is where we specify which bus is connected to which port
 * and what we want to call each bus.
 */
extern can0 MainCan;
extern can1 MotorCan;

#endif
