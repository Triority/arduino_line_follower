#include "constants.h"
#include "modules.hpp"
#include "src/tasks.hpp"

void pidCtrl() {
    ccd.collect();
    ccd.calc();
    float error = CCD_TARGET - ccd.expectation();
    if (PID_INVERT) error = -error;
    if (ccd.valid()) pid.update(error, millis());
    baseDriver.cmdVel(BASE_X_VEL, pid.output());
}

void Main() {}
