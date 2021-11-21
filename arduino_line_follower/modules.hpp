#ifndef _MODULES_HPP
#define _MODULES_HPP

#include "src/BaseDriver.hpp"
// #include "src/CCD.hpp"
#include "constants.h"
#include "src/Filter.hpp"
#include "src/GPIO.hpp"
#include "src/Motor.hpp"
#include "src/PID.hpp"
#include "src/SerialIO.hpp"
#include "src/TCRTArray.hpp"

extern GPIO led, beep;
extern GPIO tcrtL, tcrtR;
// extern CCD ccd;
extern Motor motorL, motorR;
extern BaseDriver baseDriver;
extern PID pid;
extern TCRTArray tcrtArray;

#endif  // _MODULES_HPP