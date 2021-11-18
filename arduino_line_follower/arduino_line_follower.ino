#include "modules.hpp"
#include "pit.hpp"

void setup() {
    SerialIO::begin(115200);
    led.setMode(OUTPUT);
    motorL.init();
    motorR.init();
    ccd.init();
    pitStart(1000);
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