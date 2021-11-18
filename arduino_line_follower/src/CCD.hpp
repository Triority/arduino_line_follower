#ifndef _CCD_HPP
#define _CCD_HPP

#include <stdint.h>

class CCD {
 private:
    uint8_t CLK, SI, AO;

 public:
    static const int N = 128;
    uint16_t data[N];
    CCD(uint8_t clk, uint8_t si, uint8_t ao) : CLK(clk), SI(si), AO(ao) {}
    void init();
    void update();
    void send();
    uint16_t& operator[](int i) { return data[i]; };
};

#endif  // _CCD_HPP
