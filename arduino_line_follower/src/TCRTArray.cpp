#include "TCRTArray.hpp"

void TCRTArray::setPin(const uint8_t* pins, int num) {
    N = num;
    this->pins = (uint8_t*)malloc(sizeof(uint8_t) * num);
    this->data = (uint16_t*)malloc(sizeof(uint16_t) * num);
    for (int i = 0; i < N; ++i) this->pins[i] = pins[i];
}

TCRTArray::~TCRTArray() {
    free(pins);
    free(data);
}

void TCRTArray::collect() {
    for (int i = 0; i < N; ++i) {
        data[i] = maxVal;
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], HIGH);
    }
    delayMicroseconds(10);

    noInterrupts();
    uint32_t startTime = micros();
    for (int i = 0; i < N; ++i) pinMode(pins[i], INPUT);
    interrupts();

    for (int32_t time = 0; time < maxVal;) {
        noInterrupts();
        time = micros() - startTime;
        for (int i = 0; i < N; ++i)
            if ((digitalRead(pins[i]) == LOW)) data[i] = time;
        interrupts();
    }
}
