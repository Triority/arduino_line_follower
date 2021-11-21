#include <avr/wdt.h>

#include "flags.hpp"
#include "modules.hpp"
#include "src/SerialIO.hpp"

void reset();
void startMain();
void startPID();
void remote();
void setPID();
void stopPID();

void hostCommunication() {
    beep.writeDigital(true);
    char op = Serial.read();
    switch (op) {
    case 0x00: reset(); break;
    case 0x01: startMain(); break;
    case 0x02: startPID(); break;
    case 0x03: remote(); break;
    case 0x04: setPID(); break;
    case 0x05: stopPID(); break;
    }
    beep.writeDigital(false);
}

inline void reset() {
    wdt_enable(WDTO_15MS);
    for (;;)
        ;
}

inline void startMain() { flags::startMain = true; }

inline void startPID() { flags::startPID = true; }

inline void remote() {
    float x, yaw;
    if (SerialIO::read(yaw, x)) baseDriver.cmdVel(x, -yaw);
}

inline void setPID() {
    char op = Serial.read();
    float tmp;
    if (!SerialIO::read(tmp)) return;
    switch (op) {
    case 0x00: pid.kp = tmp; break;
    case 0x01: pid.ki = tmp; break;
    case 0x02: pid.kd = tmp; break;
    }
}

inline void stopPID() { flags::startPID = false; }