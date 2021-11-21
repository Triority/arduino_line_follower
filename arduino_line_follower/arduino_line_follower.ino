#include "Main.hpp"
#include "flags.hpp"
#include "isr.hpp"
#include "modules.hpp"

void setup() {
    flags::init();
    // led.setMode(OUTPUT);
    beep.setMode(OUTPUT);
    tcrtL.setMode(INPUT), tcrtR.setMode(INPUT);
    filter.reset();

    // motorL.init();
    // motorR.init();
    ccd.init();

    // pitStart(200);
    isrStart();
    SerialIO::begin(115200);
}

void loop() {
    flags::tcrt.update();

    ccd.collect();
    // ccd.send();
    ccd.calc();
    SerialIO::write(ccd._expT, ccd._avg);
    SerialIO::flush();
    ccd.autoExp(100);
    // SerialIO::write(sizeof(int), sizeof(unsigned long));
    // SerialIO::flush();
    // {
    //     using namespace flags;
    //     SerialIO::write(tcrt[TCRT::left], tcrt[TCRT::right], tcrt[TCRT::both]);
    //     SerialIO::flush();
    // }
    // SerialIO::write(tcrtL.readDigital(), tcrtR.readDigital());
    // SerialIO::flush();
    // testCCD(true);

    // baseDriver.cmdVel(100, 0);

    // pidCtrl(true);

    // if (flags::startMain) {
    //     flags::startMain = false;
    //     Main();
    // }

    // if (flags::startPID) pidCtrl();

    // baseDriver.cmdVel(100, 0);

    // {
    //     delay(20);
    //     void hostCommunication();
    //     while (SerialIO::available()) hostCommunication();
    // }
    // // pidCtrl();
    // delay(20);
}

void serialEvent() {
    // void hostCommunication();
    // while (SerialIO::available()) hostCommunication();
}