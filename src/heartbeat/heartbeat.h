#ifndef HEARTBEAT_H
#define HEARTBEAT_H

/**
 * @brief Function that sets up basic heartbeat thread. This thread blinks a
 * light on and off with a period of two seconds. Mainly a debug to ensure the
 * car isn't dead yet.
 */
void heartbeatSetup();

#endif