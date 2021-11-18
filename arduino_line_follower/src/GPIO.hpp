#ifndef _GPIO_HPP
#define _GPIO_HPP

#include <Arduino.h>

class GPIO {
 private:
    const uint8_t _pin;

 public:
    GPIO(uint8_t pin) : _pin(pin) {}
    void setMode(uint8_t mode) { pinMode(_pin, mode); }
    bool readDigital() { return digitalRead(_pin) == HIGH; }
    int readAnalog() { return analogRead(_pin); }
    void writeDigital(bool value) { digitalWrite(_pin, value ? HIGH : LOW); }
    void writeAnalog(int value) { analogWrite(_pin, constrain(value, 0, 255)); }
};

#endif  // _GPIO_HPP