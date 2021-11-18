#ifndef _CCD_HPP
#define _CCD_HPP

#include <stdint.h>

class CCD {
 public:
    static const int N = 128;
    CCD(uint8_t clk, uint8_t si, uint8_t ao) : CLK(clk), SI(si), AO(ao) {}
    void init() const;
    void update();
    void sendImg() const;
    void calc();
    float expectation() const { return _exp; }
    bool isLost() const { return lost; }
    uint16_t& operator[](int i) { return data[i]; };
    uint16_t operator[](int i) const { return data[i]; };

 private:
    const uint8_t CLK, SI, AO;
    float _exp, _s2;  // 期望、方差
    bool lost;
    uint16_t data[N];
};

#endif  // _CCD_HPP
