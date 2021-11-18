#include "flags.hpp"
#include "modules.hpp"
#include "pit.hpp"

void setup() {
    flags::init();
    SerialIO::begin(115200);

    led.setMode(OUTPUT);
    beep.setMode(OUTPUT);
    tcrtL.setMode(INPUT), tcrtR.setMode(INPUT);

    motorL.init();
    motorR.init();
    ccd.init();
    pitStart(20);
}

void loop() {
    ccd.collect();
    ccd.calc();
    // ccd.sendImg();
    SerialIO::write(ccd.expectation(), ccd.variance());
    SerialIO::flush();

    void Main();
    if (flags::startMain) {
        flags::startMain = false;
        Main();
    }

    void pidCtrl();
    while (flags::startPID) pidCtrl();
}
