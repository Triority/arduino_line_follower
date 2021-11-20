#ifndef _CCD_HPP
#define _CCD_HPP

#include <stdint.h>

class CCD {
 public:
    static const int N = 128;
    CCD(uint8_t clk, uint8_t si, uint8_t ao, int32_t threshold) : CLK(clk), SI(si), AO(ao), thresh(threshold) {}
    void init() const;
    void collect();
    void send() const;
    void sendImg() const;
    void calc();
    bool valid() const { return isValid; }
    uint16_t& operator[](int i) { return data[i]; };
    uint16_t operator[](int i) const { return data[i]; };
    int16_t res() const { return _res; }
    int32_t s2() const { return _s2; }

 private:
    int16_t _res, _avg;
    int32_t _s2;
    const uint8_t CLK, SI, AO;
    const int32_t thresh;
    bool isValid;
    uint16_t data[N];
};

#endif  // _CCD_HPP
