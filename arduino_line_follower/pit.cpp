#include "pit.hpp"

#define USE_TIMER_1 true
#include <TimerInterrupt.h>

#include "flags.hpp"
#include "modules.hpp"

void pitStart(unsigned long interval_ms) {
    ITimer1.init();
    ITimer1.setInterval(interval_ms, pitHandler);
}

void pitHandler() {
    {
        using namespace flags;
        tcrt.update();
        bool l = true, r = true;
        for (int i = 0; i < 5; ++i) l &= tcrtL.readDigital(), r &= tcrtR.readDigital();
        if (l) tcrt.set(TCRT::left);
        if (r) tcrt.set(TCRT::right);
        if (tcrt[TCRT::left] && tcrt[TCRT::right]) tcrt.set(TCRT::both);
    }
}