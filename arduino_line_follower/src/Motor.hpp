#ifndef _MOTOR_HPP
#define _MOTOR_HPP

#define L298N

#include <Arduino.h>

#ifdef L298N

class Motor {
 private:
    const uint8_t pwmPin, dirA, dirB;
    bool dir;

 public:
    Motor(uint8_t pwm_pin, uint8_t inA, uint8_t inB) : pwmPin(pwm_pin), dirA(inA), dirB(inB) {}
    void init() {
        pinMode(pwmPin, OUTPUT);
        pinMode(dirA, OUTPUT);
        pinMode(dirB, OUTPUT);
        setPwm(0);
    }
    void setPwm(int32_t pwm) { analogWrite(pwmPin, min(pwm, 255)); }
    void setDir(bool dir) {
        this->dir = dir;
        digitalWrite(dirA, dir ? LOW : HIGH);
        digitalWrite(dirB, dir ? HIGH : LOW);
    }
    void toggleDir() { setDir(!dir); }
    void setSpeed(int32_t pwm) {
        if (pwm > 0) setDir(true);
        else {
            setDir(false);
            pwm = -pwm;
        }
        setPwm(pwm + 5 * min(pwm, 10));
    }
};

#else  // L298N
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
#endif  // L298N