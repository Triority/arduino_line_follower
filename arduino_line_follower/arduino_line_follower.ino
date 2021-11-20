#include "Main.hpp"
#include "flags.hpp"
#include "modules.hpp"
#include "pit.hpp"

void setup() {
    flags::init();

    // led.setMode(OUTPUT);
    beep.setMode(OUTPUT);
    tcrtL.setMode(INPUT), tcrtR.setMode(INPUT);

    // motorL.init();
    // motorR.init();
    ccd.init();
    // pitStart(200);
    SerialIO::begin(115200);
}

void loop() {
    testCCD(false);

    // pidCtrl();

    // if (flags::startMain) {
    //     flags::startMain = false;
    //     Main();
    // }

    // if (flags::startPID) pidCtrl();

    // baseDriver.cmdVel(100, 0);

    // void hostCommunication();
    // while (SerialIO::available()) hostCommunication();
    // pidCtrl();
    // delay(20);
}

void serialEvent() {
    // void hostCommunication();
    // while (SerialIO::available()) hostCommunication();
}