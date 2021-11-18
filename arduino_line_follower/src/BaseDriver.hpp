#ifndef _BASE_DRIVER_HPP
#define _BASE_DRIVER_HPP

#include "Motor.hpp"

class BaseDriver {
 private:
    Motor &L, &R;
    bool dropSpeed;

 public:
    BaseDriver(Motor &motorL, Motor &motorR, bool doDropSpeed = true) : L(motorL), R(motorR), dropSpeed(doDropSpeed) {}
    void init();
    void cmdVel(float x, float yaw) {
        if (dropSpeed) {
            L.setSpeed(x - yaw);
            R.setSpeed(x + yaw);
        } else {
            if (yaw > 0) {
                L.setSpeed(x - yaw * 2);
                R.setSpeed(x);
            } else {
                L.setSpeed(x);
                R.setSpeed(x + yaw * 2);
            }
        }
    }
    void hardBrake() {
        L.toggleDir(), R.toggleDir();
        delay(100);
        L.setPwm(0), R.setPwm(0);
    }
};

#endif  // _BASE_DRIVER_HPP