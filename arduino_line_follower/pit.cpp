#include "pit.hpp"

#define USE_TIMER_1 true
#include <TimerInterrupt.h>

#include "modules.hpp"

void pitStart(unsigned long interval_ms) {
    ITimer1.init();
    ITimer1.setInterval(interval_ms, pitHandler);
}

void pitHandler() {
    static bool toggle = false;
    led.writeDigital(toggle);
    toggle = !toggle;
}