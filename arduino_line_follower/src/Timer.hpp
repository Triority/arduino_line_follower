#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <Arduino.h>

class Timer {
    unsigned long t;

 public:
    Timer() : t(millis()) {}
    bool ready(unsigned long ms) {
        if (millis() - t > ms) {
            t = millis();
            return true;
        }
        return false;
    }
    void period(unsigned long ms) {
        while (millis() - t < ms)
            ;
        t = millis();
    }
};

#endif  // _TIMER_HPP