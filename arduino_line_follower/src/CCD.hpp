#ifndef _CCD_HPP
#define _CCD_HPP

#include <stdint.h>

class CCD {
 public:
    static const int N = 128;
    CCD(uint8_t clk, uint8_t si, uint8_t ao, int16_t sep, int16_t threshold_low, int16_t threshold_high)
        : CLK(clk), SI(si), AO(ao), Sep(sep), threshLow(threshold_low), threshHigh(threshold_high) {}
    void init();
    void collect();
    void expDelay(unsigned long ms) const;
    void autoExp(int16_t targetAvg);
    void send() const;
    void sendImg() const;
    void calc();
    bool valid() const { return isValid; }
    int16_t& operator[](int i) { return data[i]; };
    int16_t operator[](int i) const { return data[i]; };
    int16_t res() const { return _res; }
    int16_t avg() const { return _avg; }
    int16_t expTime() const { return _expT; }

 private:
    unsigned long _t;
    int16_t _expT = 0;
    int16_t _res = N >> 1, _avg;
    const uint8_t CLK, SI, AO;
    const int16_t Sep, threshLow, threshHigh;
    bool isValid;
    int16_t data[N];
};

#endif  // _CCD_HPP
