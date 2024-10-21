
#include "heartbeat.h"
#include "common.h"

// TODO: this was defined in params.h; should we move this there?
#define THREAD_STACK_SIZE_HEARTBEAT 512
#define THREAD_PRIORITY_HEARTBEAT LOWPRIO

static THD_WORKING_AREA(wa_heartbeat, THREAD_STACK_SIZE_HEARTBEAT);
/**
 * @brief Construct a new thd function object to handle sending telemetry data back to pit/base station
 *
 */
static THD_FUNCTION(heartbeat, arg) {
    (void) arg;
    while (true){
        digitalWrite(LED_BUILTIN, HIGH);
        chThdSleepMilliseconds(1000);
        digitalWrite(LED_BUILTIN, LOW);
        chThdSleepMilliseconds(1000);
    }
}
/**
 * @brief One-time call function to set up the heartbeat thread
 *
 */
void heartbeatSetup() {
    chThdCreateStatic(wa_heartbeat, sizeof(wa_heartbeat),THREAD_PRIORITY_HEARTBEAT, heartbeat, NULL);
}