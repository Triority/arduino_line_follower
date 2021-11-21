#include "Main.hpp"

#include "constants.h"
#include "flags.hpp"
#include "modules.hpp"
#include "src/tasks.hpp"

// void testCCD(bool sendImg) {
//     ccd.collect();
//     ccd.calc();
//     if (sendImg) ccd.send();
//     else {
//         SerialIO::write(ccd.expTime(), ccd.avg(), ccd.res());
//         SerialIO::flush();
//     }
//     ccd.autoExp(100);
// }

void pidCtrl(bool send) {
    tcrtArray.collect();
    tcrtArray.calc();
    if (tcrtArray.valid()) {
        int error = TCRT_TARGET - tcrtArray.res();
        if (PID_INVERT) error = -error;

        pid.update(error, millis());
        if (send) {
            SerialIO::write(error, pid.output());
            SerialIO::flush();
        }
        baseDriver.cmdVel(BASE_X_VEL, int32_t(pid.output()) >> 4);
    }
    // delay(100);
}

void Main() {
    WaitRight(pidCtrl());
    baseDriver.hardBrake();
    for (;;)
        ;
}
