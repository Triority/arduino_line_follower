#include "Main.hpp"

#include "constants.h"
#include "flags.hpp"
#include "modules.hpp"
#include "src/tasks.hpp"

void testCCD(bool sendImg) {
    ccd.collect();
    ccd.calc();
    if (sendImg) ccd.send();
    else {
        SerialIO::write(ccd.expTime(), ccd.avg(), ccd.res());
        SerialIO::flush();
    }
    ccd.autoExp(100);
}

void pidCtrl(bool send) {
    ccd.collect();
    ccd.calc();
    int error = CCD_TARGET - ccd.res();
    if (PID_INVERT) error = -error;
    error = filter.update(error);
    pid.update(error, millis());
    if (send) {
        SerialIO::write(error, pid.output());
        SerialIO::flush();
    }
    baseDriver.cmdVel(BASE_X_VEL, pid.output());
    ccd.autoExp(100);
}

void Main() {
    WaitRight(pidCtrl());
    baseDriver.hardBrake();
    for (;;)
        ;
}
