#ifndef MYBITSET_H_
#define MYBITSET_H_

#include <stdint.h>

template <unsigned N> class MyBitset {
 private:
    uint32_t data[(N + 31) >> 5];

 public:
    void reset(int i) { data[i >> 5] &= ~(1 << (i & 31)); }
    void reset(void) {
        for (int i = 0; i < (N + 31) >> 5; ++i) data[i] = 0;
    }
    void set(int i, bool state = true) {
        if (state) (data[i >> 5] |= 1 << (i & 31));
        else
            reset(i);
    }
    bool any() const {
        for (int i = 0; i < (N + 31) >> 5; ++i)
            if (data[i]) return true;
        return false;
    }
    bool check(int i) const { return data[i >> 5] & (1 << (i & 31)); }
    bool operator[](int i) const { return check(i); }
};
#endif  // MYBITSET_H_