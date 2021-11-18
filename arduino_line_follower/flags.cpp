#include "flags.hpp"

#include "constants.h"
namespace flags {

DelayChecker<TCRT::__size> tcrt;

void init() {
    tcrt.init();

    tcrt.setDuration(TCRT::left, FLAG_DURATION_TCRT_SIDE);
    tcrt.setDuration(TCRT::right, FLAG_DURATION_TCRT_SIDE);
    tcrt.setDuration(TCRT::both, FLAG_DURATION_TCRT_BOTH);
}

bool startPID, startMain;
}  // namespace flags