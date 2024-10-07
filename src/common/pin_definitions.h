/**
 * @file pin_definitions.h
 * @brief Holds macros that serve as a hardware abstraction layer. Copied from TBS
 * @version 0.01
 *
 *
 */

#ifndef BOTTOM_SHELL_H
#define BOTTOM_SHELL_H

//TODO: Find pin for TRIGGER_MODE

//Teensy 4.1 pin mappings, all names are referenced to the Eagle schematics

//Left side of the board diagram
#define TWELVE_V_MEASURE A0 //14, on the Eagle schematic as "12V_MEASURE"
                             //15 is empty
#define THROT1_IN A2 //16
#define THROT2_IN A3 //17
#define BPT_FR_IN A4 //18
#define BPT_RR_IN A5 //19
#define BPT_FL_IN A6 //20
#define BPT_RL_IN A7 //21
#define CAN0_TX A8 //22
#define CAN0_RX A9 //23
#define BRAKE_SWITCH A10 //24 EX7
                            //A11 25 is empty
                            //A12 26 is empty
                            //A13 27 is empty
#define RT_CTRL A14 //38
#define LT_CTRL A15 //39
#define BRAKE_CTRL A16 //40
#define RUNNING_LIGHTS A17 //41
                            //30 is empty
                            //31 is empty
#define BPS_STROBE 3
                            //4 is empty
#define FORWARD_REVERSE_IN 5  // EX1
#define V_BAT VBAT

//Right side of the board diagram
#define V_USB VUSB
//#define USB0_D- D-
//#define USB0_D+ D+
#define CAN1_RX 0
#define CAN_TX 1

//pins that were added on the updated bottom shell board schematic
#define GPS_RX 7
#define GPS_TX 8
                            //28 is empty
                            //29 is empty

#define CAN0_STB 34
#define CAN1_STB 35
#define EX4 10 // CHARGE_ENABLE/CHARGE_DISABLE
#define EX5 11
#define EX6 12
//heartbeat is on 13, DO NOT USE
                            //32 is empty
#define RECALIBRATION_MODE_PIN 9 // EX 3
#define TRIGGER_MODE 6 // EX 2
#define GPS_MISC 33
#define GPS_TRIG 36
#define GPS_PPS 37



#endif