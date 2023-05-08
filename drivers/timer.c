#include <stdint.h>
#include "timer.h"
#include "io.h"

#define TIMER_LOAD_VALUE 0x100000

static uint32_t* const TIMER_LOAD  = (uint32_t*)0x101E2000;
static uint32_t* const TIMER_VALUE = (uint32_t*)0x101E2004;
static uint32_t* const TIMER_CTL   = (uint32_t*)0x101E202C;

void timer_init() {
    // Set the load value for the timer
    *TIMER_LOAD = TIMER_LOAD_VALUE;
    // Enable the timer and set it to periodic mode
    *TIMER_CTL = 0x62;
}

void timer_wait(uint32_t us) {
    uint32_t start_time = *TIMER_VALUE;
    uint32_t target_time = start_time + (us * (TIMER_LOAD_VALUE / 1000000));
    if (target_time < start_time) {
        // Handle timer wrap-around
        while (*TIMER_VALUE > start_time);
    }
    while (*TIMER_VALUE < target_time);
}
