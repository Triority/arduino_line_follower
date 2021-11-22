#include "Main.hpp"
#include "flags.hpp"
#include "isr.hpp"
#include "modules.hpp"
#include "tasks.hpp"

void setup() {
    flags::init();
    // led.setMode(OUTPUT);
    // beep.setMode(OUTPUT);
    tcrtArray.init();
    tcrtL.setMode(INPUT), tcrtR.setMode(INPUT);
    motorL.init(), motorR.init();
    isrStart();
    SerialIO::begin(115200);
}

void loop() {
    TaskEssentials();
    // testTCRT();
    // testLR();

    if (flags::startMain) Main();
    if (flags::startPID) pidCtrl(true);
}
