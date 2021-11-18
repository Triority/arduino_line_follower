#ifndef _CCD_HPP
#define _CCD_HPP

#include <stdint.h>

class CCD {
 public:
    static const int N = 128;
    CCD(uint8_t clk, uint8_t si, uint8_t ao, float threshold) : CLK(clk), SI(si), AO(ao), thresh(threshold) {}
    void init() const;
    void update();
    void sendImg() const;
    void calc();
    float expectation() const { return _exp; }
    float variance() const { return _s2; }
    bool valid() const { return isValid; }
    uint16_t& operator[](int i) { return data[i]; };
    uint16_t operator[](int i) const { return data[i]; };

 private:
    const uint8_t CLK, SI, AO;
    const float thresh;
    float _exp, _s2;  // 期望、方差
    bool isValid;
    uint16_t data[N];
};

#endif  // _CCD_HPP
