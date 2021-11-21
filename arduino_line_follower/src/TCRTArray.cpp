#include "TCRTArray.hpp"

#include "SerialIO.hpp"

TCRTArray::TCRTArray(const uint8_t* pins, int8_t num, int16_t threshLow, int16_t threshHigh)
    : N(num), low(threshLow), high(threshHigh) {
    this->pins = (uint8_t*)malloc(sizeof(uint8_t) * num);
    this->data = (int16_t*)malloc(sizeof(int16_t) * num);
    for (int i = 0; i < N; ++i) this->pins[i] = pins[i];
}

TCRTArray::~TCRTArray() {
    free(pins);
    free(data);
}

void TCRTArray::init() {
    for (int i = 0; i < N; ++i) pinMode(pins[i], INPUT);
}

void TCRTArray::collect() {
    for (int i = 0; i < N; ++i) data[i] = analogRead(pins[i]);
}

void TCRTArray::send() const {
    for (int i = 0; i < N; ++i) SerialIO::write(data[i]);
    SerialIO::flush();
}

void TCRTArray::calc() {
    _valid = false;
    int32_t m0 = 0, m1 = 0;
    for (int32_t i = 0; i < N; ++i) {
        _valid |= data[i] >= high;  //
        if (data[i] >= low) {
            m0 += data[i];
            m1 += (i << 10) * data[i];
        }
    }
    if (_valid) _res = m1 / m0;
}
