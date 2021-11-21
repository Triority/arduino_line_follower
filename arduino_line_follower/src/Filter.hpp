#ifndef _FILTER_HPP
#define _FILTER_HPP

template <typename T, unsigned N> class SMA {
 private:
    unsigned char n;
    T data[N];

 public:
    float val;
    void reset() {
        n = 0;
        val = 0.f;
        for (int i = 0; i < N; ++i) data[i] = 0;
    }
    float update(T x) {
        val += (float)(x - data[n]) / N;
        data[n++] = x;
        if (n == N) n = 0;
        return val;
    }
};

#endif  // _FILTER_HPP