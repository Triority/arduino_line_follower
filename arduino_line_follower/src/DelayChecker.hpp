#ifndef _FLAGCHECKER_H
#define _FLAGCHECKER_H

#include <Arduino.h>

#include "MyBitset.hpp"
// #include "SerialIO.hpp"

template <unsigned N> class DelayChecker {
 private:
    int32_t duration[N], targetTime[N];
    char trigger[N];
    MyBitset<N> flags;

 public:
    void init() {
        for (int i = 0; i < N; ++i) trigger[i] = -1;
    }
    void setDuration(int32_t i, int32_t time_ms) { duration[i] = time_ms; }
    void bind(int32_t i, int32_t j) { trigger[i] = j; }
    template <typename... T> void bind(int32_t i, int32_t j, T... t) { bind(i, j), bind(j, t...); }
    void bindDiscard(int32_t i, int32_t j) { trigger[i] = j + N; }
    void discard(int32_t i) {
        if (flags.check(i)) {
            flags.reset(i);
            if (trigger[i] != -1) {
                if (trigger[i] >= N) discard(trigger[i] - N);
                else
                    set(trigger[i]);
            }
        }
    }
    void update() {
        for (int i = 0; i < N; ++i)
            // if (flags[i] && (int32_t)millis() - targetTime[i] >= 0) {
            //     SerialIO::write(millis(), targetTime[i]);
            //     discard(i);
            // } else {
            //     SerialIO::write(0, 0);
            // }
            if (flags[i] && (int32_t)millis() - targetTime[i] >= 0) discard(i);
        // SerialIO::flush();
    }
    bool check(int32_t i) const { return flags[i]; }
    bool operator[](int32_t i) const { return check(i); }
    char get() {
        for (int i = 0; i < N; ++i)
            if (flags[i]) return i;
        return -1;
    }
    void set(int32_t i) {
        flags.set(i);
        targetTime[i] = millis() + duration[i];
    }
    bool any() const { return flags.any(); }
};

#endif  // FLAGCHECKER_H_