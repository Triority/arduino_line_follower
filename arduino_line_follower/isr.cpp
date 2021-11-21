#include "isr.hpp"

#include "flags.hpp"
#include "modules.hpp"
#include "src/SerialIO.hpp"

void tcrtLCB();
void tcrtRCB();

void isrStart() {
    tcrtL.attachInterrupt(tcrtLCB, CHANGE);
    tcrtR.attachInterrupt(tcrtRCB, CHANGE);
    // attachInterrupt(tcrtL.pin(), tcrtLCB, CHANGE);
    // attachInterrupt(tcrtR.pin(), tcrtRCB, CHANGE);
}

void tcrtBothCB() {
    using namespace flags;
    if (tcrt[TCRT::left] && tcrt[TCRT::right]) tcrt.set(TCRT::both);
}

void tcrtLCB() {
    using namespace flags;
    tcrt.set(TCRT::left);
    tcrtBothCB();
}

void tcrtRCB() {
    using namespace flags;
    tcrt.set(TCRT::right);
    tcrtBothCB();
}
