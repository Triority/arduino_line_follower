#ifndef _MOTOR_HPP
#define _MOTOR_HPP

#ifndef _L298N
#define _L298N false
#endif

#include <Arduino.h>

#if (_L298N)

class Motor {
 private:
    const uint8_t pwmPin, dirA, dirB;
    int16_t deadS, deadG;
    bool dir;

 public:
    Motor(uint8_t pwm_pin, uint8_t inA, uint8_t inB, int16_t deadZoneSize, int16_t deadZoneGain)
        : pwmPin(pwm_pin), dirA(inA), dirB(inB) {
        setDeadZone(deadZoneSize, deadZoneGain);
    }
    void init() {
        pinMode(pwmPin, OUTPUT);
        pinMode(dirA, OUTPUT);
        pinMode(dirB, OUTPUT);
        setPwm(0);
    }
    void setDeadZone(int16_t deadZoneSize, int16_t deadZoneGain) { deadS = deadZoneSize, deadG = deadZoneGain; }
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
        setPwm(pwm + deadG * min(pwm, deadS));
    }
};

#else  // _L298N

class Motor {
 private:
    const uint8_t pwmPin, dirPin;
    int16_t deadS, deadG;
    const bool invert;
    bool dir;

 public:
    Motor(uint8_t pwm_pin, uint8_t dir_pin, bool isInverted, int16_t deadZoneSize, int16_t deadZoneGain)
        : pwmPin(pwm_pin), dirPin(dir_pin), invert(isInverted) {
        setDeadZone(deadZoneSize, deadZoneGain);
    }
    void setDeadZone(int16_t deadZoneSize, int16_t deadZoneGain) { deadS = deadZoneSize, deadG = deadZoneGain; }
    void init() {
        pinMode(pwmPin, OUTPUT);
        pinMode(dirPin, OUTPUT);
        setPwm(0);
    }
    void setPwm(int32_t pwm) { analogWrite(pwmPin, min(pwm, 255)); }
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
        setPwm(pwm + deadG * min(pwm, deadS));
    }
};

#endif  // _L298N

#endif  // _MOTOR_HPP