#ifndef _MOTOR_HPP
#define _MOTOR_HPP

#include <Arduino.h>

class Motor {
 private:
    const uint8_t pwmPin, dirPin;
    const bool invert;
    bool dir;

 public:
    Motor(uint8_t pwm_pin, uint8_t dir_pin, bool isInverted) : pwmPin(pwm_pin), dirPin(dir_pin), invert(isInverted) {}
    void init() {
        pinMode(pwmPin, OUTPUT);
        pinMode(dirPin, OUTPUT);
        setPwm(0);
    }
    void setPwm(int32_t pwm) { analogWrite(pwmPin, constrain(pwm, 0, 255)); }
    void setDir(bool dir) {
        this->dir = dir;
        digitalWrite(dirPin, dir ^ invert ? LOW : HIGH);
    }
    void toggleDir() { setDir(!dir); }
    void setSpeed(int32_t pwm) {
        if (pwm > 0) setDir(true);
        else {
            setDir(false);
            pwm = -pwm;
        }
        setPwm(pwm);
    }
};

#endif  // _MOTOR_HPP