#include "CCD.hpp"

#include <Arduino.h>
#include <float.h>

void CCD::init() const {
    pinMode(CLK, OUTPUT);
    pinMode(SI, OUTPUT);
    pinMode(AO, INPUT);
}

void CCD::update() {
    digitalWrite(CLK, HIGH);
    digitalWrite(SI, LOW);
    digitalWrite(CLK, LOW);
    digitalWrite(SI, HIGH);
    digitalWrite(CLK, HIGH);
    digitalWrite(SI, LOW);
    for (int i = 0; i < N; ++i) {
        digitalWrite(CLK, LOW);
        data[i] = analogRead(AO);
        digitalWrite(CLK, HIGH);
    }
}

void CCD::calc() {
    int32_t m1 = 0, m2 = 0, s = 0;
    for (int i = 0; i < N; ++i) {
        int32_t cur = 1024 - data[i];
        s += cur;
        m1 += cur * i;
        m2 += cur * i * i;
    }
    if (s == 0) {
        _s2 = FLT_MAX;
        lost = true;
        return;
    }
    _exp = (float)m1 / s;
    _s2 = (float)m2 / s - _exp * _exp;
}

void CCD::sendImg() const {
    Serial.write("\x00\xff\x01\x00", 4);
    for (int i = 0; i < N; ++i) {
        Serial.write(data[i] >> 8);
        Serial.write(data[i] & 0XFF);
    }
}
