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
    Main();
}

void loop() {
    flags::tcrt.update();

    ccd.collect();
    // ccd.send();
    ccd.calc();
    SerialIO::write(ccd.res());
    SerialIO::flush();
    ccd.autoExp(100);
    // SerialIO::write(sizeof(int), sizeof(unsigned long));
}

void serialEvent() {
    // void hostCommunication();
    // while (SerialIO::available()) hostCommunication();
}