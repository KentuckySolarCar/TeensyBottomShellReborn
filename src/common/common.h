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

/**
 * @brief A templated function for parsing a CAN message buffer into desired data types.
 * @details This 
 */
template<typename T, int offset>
T parseCANBuf(const CAN_message_t &msg) {
  // make sure we can store read enough data from CAN buffer
  constexpr size_t dataBounds = sizeof(T)*(offset+1);
  static_assert(dataBounds <= 8, "can't read buffer! index out of bounds");
  T ret;
  memcpy(&ret, &msg.buf[0] + offset * sizeof(T), sizeof(T));
  return ret;
}

#endif