#ifndef _FLAGCHECKER_H
#define _FLAGCHECKER_H

#include <Arduino.h>

#include "MyBitset.hpp"

template <unsigned N> class DelayChecker {
 private:
    int duration[N], targetTime[N];
    char trigger[N];
    MyBitset<N> flags;

 public:
    void init() {
        for (int i = 0; i < N; ++i) trigger[i] = -1;
    }
    void setDuration(int i, int time_ms) { duration[i] = time_ms; }
    void bind(int i, int j) { trigger[i] = j; }
    template <typename... T> void bind(int i, int j, T... t) { bind(i, j), bind(j, t...); }
    void bindDiscard(int i, int j) { trigger[i] = j + N; }
    void discard(int i) {
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
            if (flags[i] && millis() - targetTime[i] >= 0) discard(i);
    }
    bool check(int i) const { return flags[i]; }
    bool operator[](int i) const { return check(i); }
    char get() {
        for (int i = 0; i < N; ++i)
            if (flags[i]) return i;
        return -1;
    }
    void set(int i) {
        flags.set(i);
        targetTime[i] = millis() + duration[i];
    }
    bool any() const { return flags.any(); }
};

#endif  // FLAGCHECKER_H_