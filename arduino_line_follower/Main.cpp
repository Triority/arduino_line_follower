#include "Main.hpp"

#include "constants.h"
#include "flags.hpp"
#include "modules.hpp"
#include "tasks.hpp"

float vel_X = BASE_X_VEL;

void testTCRT(bool sendArray) {
    tcrtArray.collect();
    if (timer.ready(PID_PERIOD_MS)) {
        tcrtArray.calc();
        if (sendArray) tcrtArray.send();
        else {
            SerialIO::write(tcrtArray.valid(), tcrtArray.res());
            SerialIO::flush();
        }
        tcrtArray.reset();
    }
}

void testLR() {
    using namespace flags;
    SerialIO::write(tcrt[TCRT::left], tcrt[TCRT::right], tcrt[TCRT::both]);
    SerialIO::flush();
}

void pidCtrl(bool send) {
    tcrtArray.collect();
    if (timer.ready(PID_PERIOD_MS)) {
        tcrtArray.calc();
        if (tcrtArray.valid()) {
            int error = TCRT_TARGET - tcrtArray.res();
            if (PID_INVERT) error = -error;

            pid.update(error);
            if (send) {
                SerialIO::write(error, pid.output());
                SerialIO::flush();
            }
        }
        baseDriver.cmdVel(vel_X, pid.output() / 1024);
        tcrtArray.reset();
    }
}

void Main() {
    WaitRight(pidCtrl());
    baseDriver.hardBrake();
    for (;;)
        ;
}
