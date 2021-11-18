#ifndef _MODULES_HPP
#define _MODULES_HPP

#include "src/BaseDriver.hpp"
#include "src/CCD.hpp"
#include "src/GPIO.hpp"
#include "src/Motor.hpp"
#include "src/SerialIO.hpp"

extern GPIO led;
extern CCD ccd;
extern Motor motorL, motorR;
extern BaseDriver baseDriver;

#endif  // _MODULES_HPP