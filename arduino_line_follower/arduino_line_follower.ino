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

int a;
float b;

void loop() {
    // SerialIO::write(a, b);
    // SerialIO::flush();
    ccd.update();
    ccd.sendImg();
    delay(20);
}

void serialEvent() {
    // while (SerialIO::available()) {
    //     SerialIO::read(a);
    //     SerialIO::write(a, b);
    //     SerialIO::flush();
    // }
}