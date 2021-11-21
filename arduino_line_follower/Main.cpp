#include "Main.hpp"

#include "constants.h"
#include "modules.hpp"
#include "src/tasks.hpp"

void testCCD(bool sendImg) {
    ccd.collect();
    ccd.calc();
    if (sendImg) ccd.send();
    else {
        SerialIO::write(ccd.res(), ccd.s2());
        SerialIO::flush();
    }
}

void pidCtrl(bool send) {
    ccd.collect();
    ccd.calc();
    int error = CCD_TARGET - ccd.res();
    if (PID_INVERT) error = -error;
    error = filter.update(error);
    pid.update(error, millis());
    if (send) {
        SerialIO::write(ccd.s2(), error, pid.output());
        SerialIO::flush();
    }
    baseDriver.cmdVel(BASE_X_VEL, pid.output());
}

void Main() {}
