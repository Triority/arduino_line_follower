#ifndef _MOTOR_HPP
#define _MOTOR_HPP

#include <Arduino.h>

class Motor {
 private:
    const uint8_t pwmPin, dirPin;
    bool dir;

 public:
    Motor(uint8_t pwm_pin, uint8_t dir_pin) : pwmPin(pwm_pin), dirPin(dir_pin) {}
    void init() {
        pinMode(pwmPin, OUTPUT);
        pinMode(dirPin, OUTPUT);
    }
    void setPwm(uint8_t pwm) { analogWrite(pwmPin, constrain(pwm, 0, 255)); }
    void setDir(uint8_t dir) {
        this->dir = dir;
        digitalWrite(dirPin, dir ? LOW : HIGH);
    }
    void toggleDir() { setDir(!dir); }
    void setSpeed(int pwm) {
        if (pwm > 0) setDir(true);
        else {
            setDir(false);
            pwm = -pwm;
        }
        setPwm(pwm);
    }
};

#endif  // _MOTOR_HPP