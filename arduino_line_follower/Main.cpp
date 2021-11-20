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

void pidCtrl() {
    ccd.collect();
    ccd.calc();
    int error = CCD_TARGET - ccd.res();
    if (PID_INVERT) error = -error;
    pid.update(error, millis());
    SerialIO::write(error, pid.output());
    SerialIO::flush();
    baseDriver.cmdVel(BASE_X_VEL, pid.output());
}

void Main() {}
