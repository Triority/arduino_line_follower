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

void testAll() {
    tcrtArray.collect();
    if (timer.ready(PID_PERIOD_MS)) {
        tcrtArray.calc();
        using namespace flags;
        SerialIO::write(tcrt[TCRT::left], tcrt[TCRT::right], tcrt[TCRT::both]);
        tcrtArray.send();
        tcrtArray.reset();
    }
}

void pidCtrl(bool send) {
    tcrtArray.collect();
    if (timer.ready(PID_PERIOD_MS)) {
        tcrtArray.calc();
        int error = TCRT_TARGET - tcrtArray.res();
        if (PID_INVERT) error = -error;

        pid.update(error);
        if (send) {
            SerialIO::write(error, pid.output() * PID_GAIN * 10);
            SerialIO::flush();
        }
        baseDriver.cmdVel(vel_X, pid.output() * PID_GAIN);
        tcrtArray.reset();
    }
}

void LRStop() {
    using namespace flags;
    if (startPID && (tcrt[TCRT::left] || tcrt[TCRT::right])) {
        startPID = false;
        baseDriver.hardBrake();
    }
}

void turnLeft(unsigned long turn, unsigned long staight = 300) {
    baseDriver.hardBrake();
    WaitDelayOnce(baseDriver.cmdVel(100, 0), staight);
    baseDriver.hardBrake();
    WaitDelayOnce(baseDriver.cmdVel(50, 200), turn);
    baseDriver.hardBrake();
}

void turnRight(unsigned long turn, unsigned long staight = 300) {
    baseDriver.hardBrake();
    WaitDelayOnce(baseDriver.cmdVel(100, 0), staight);
    baseDriver.hardBrake();
    WaitDelayOnce(baseDriver.cmdVel(50, -200), turn);
    baseDriver.hardBrake();
}

void setPIDStraight() {
    pid.set(15000, 0, 5410);
    vel_X = 150;
}

void setPIDCurve() {
    pid.set(10740, 0, 1338);
    vel_X = 150;
}

void setPIDDrop() {
    pid.set(16344, 0, 0);
    vel_X = 100;
}

void Main() {
    flags::startMain = false;

    setPIDStraight();
    WaitRight(pidCtrl());
    turnRight(450);

    setPIDStraight();
    WaitDelay(pidCtrl(), 500);
    WaitLeft(pidCtrl());
    WaitDelay(pidCtrl(), 500);
    WaitLeft(pidCtrl());
    turnLeft(700);

    setPIDStraight();
    WaitDelay(pidCtrl(), 500);
    WaitRight(pidCtrl());
    turnRight(350, 100);

    setPIDDrop();
    WaitLeft(pidCtrl());
    turnLeft(700);

    setPIDCurve();
    WaitDelay(pidCtrl(), 500);
    WaitLeft(pidCtrl());
    turnLeft(700);

    setPIDStraight();
    WaitDelay(pidCtrl(), 500);
    WaitLeft(pidCtrl());
    turnLeft(450);

    setPIDStraight();
    WaitDelay(pidCtrl(), 700);
    WaitLeft(pidCtrl());
    WaitDelay(pidCtrl(), 700);
    WaitLeft(pidCtrl());
    turnLeft(600);

    setPIDCurve();
    WaitDelay(pidCtrl(), 700);
    WaitLeft(pidCtrl());
    turnLeft(550);

    setPIDStraight();
    WaitLeft(pidCtrl());
    WaitDelay(pidCtrl(), 5000);

    setPIDCurve();
    WaitRight(pidCtrl());
    turnRight(450);

    setPIDStraight();
    WaitLeft(pidCtrl());
    turnLeft(500);
    WaitRight(pidCtrl());
    turnRight(500);
    WaitDelay(pidCtrl(), 1000);

    baseDriver.hardBrake();
}
