#ifndef _FLAGS_HPP
#define _FLAGS_HPP

#include "src/DelayChecker.hpp"

namespace flags {
namespace TCRT {
enum { left, right, both, __size };
}
extern DelayChecker<TCRT::__size> tcrt;
void init();
};  // namespace flags

#endif  // _FLAGS_HPP