#ifndef _TCRT_ARRAY_HPP
#define _TCRT_ARRAY_HPP

#include <Arduino.h>

class TCRTArray {
    int8_t N;
    uint8_t* pins = nullptr;
    uint16_t* data = nullptr;
    uint16_t maxVal = 32767;

 public:
    TCRTArray(uint8_t* pins, int N) { setPin(pins, N); }
    void setPin(const uint8_t* pins, int num);
    ~TCRTArray();

    void collect();

    void calc();
};

#endif  // _TCRT_ARRAY_HPP