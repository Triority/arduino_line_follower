#ifndef _FLAGS_HPP
#define _FLAGS_HPP

#include "src/DelayChecker.hpp"

namespace flags {
namespace TCRT {
enum {
    both,
    left,
    right,
    __size,
};
}
extern DelayChecker<TCRT::__size> tcrt;
void init();

extern bool startPID, startMain;
};  // namespace flags

#endif  // _FLAGS_HPP