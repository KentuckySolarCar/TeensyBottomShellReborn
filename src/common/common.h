#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include "can_setup.h"
#include "pin_definitions.h"
#include <ChRt.h>

#define BAUD_RATE 500000

#define LIGHTS_PRIO (NORMALPRIO + 2)
#define LIGHTS_WA 4096
#define LIGHTS_SLEEP 100

#define ROUTER_PRIO (NORMALPRIO + 3)
#define ROUTER_WA 2048
#define ROUTER_SLEEP 40

#define HEARTBEAT_PRIO (LOWPRIO)
#define HEARTBEAT_WA 512
#define HEARTBEAT_SLEEP 100

#endif