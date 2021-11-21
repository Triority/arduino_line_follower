#include "CCD.hpp"

#include <Arduino.h>
#include <float.h>

void CCD::init() {
    pinMode(CLK, OUTPUT);
    pinMode(SI, OUTPUT);
    pinMode(AO, INPUT);
    collect();
}

void CCD::collect() {
    _t = millis();
    int32_t sum = 0;
    digitalWrite(CLK, HIGH);
    digitalWrite(SI, LOW);
    digitalWrite(CLK, LOW);
    digitalWrite(SI, HIGH);
    digitalWrite(CLK, HIGH);
    digitalWrite(SI, LOW);
    for (int i = 0; i < N; ++i) {
        digitalWrite(CLK, LOW);
        data[i] = analogRead(AO);
        sum += (int32_t)data[i];
        digitalWrite(CLK, HIGH);
    }
    _avg = sum / N;
}

void CCD::expDelay(unsigned long ms) const {
    while (millis() - _t < ms)
        ;
}

void CCD::autoExp(int16_t targetAvg) {
    _expT += targetAvg - _avg;
    _expT = constrain(_expT, 0, 100);
    expDelay(_expT);
}

void CCD::calc() {
    int16_t l = -1, r = -1;

    for (int i = Sep; i < N - Sep; ++i) {
        if (abs(data[i] - data[i - Sep]) <= threshLow && data[i] - data[i + Sep] >= threshHigh) l = i + Sep;
        if (abs(data[i] - data[i + Sep]) <= threshLow && data[i] - data[i - Sep] >= threshHigh) r = i - Sep;
    }

    isValid = l != -1 && r != -1;
    if (isValid) _res = (l + r) >> 1;
}

void CCD::send() const {
    Serial.write("\x00\xff\x01\x00", 4);
    for (int i = 0; i < N; ++i) {
        Serial.write(data[i] >> 8);
        Serial.write(data[i] & 0XFF);
    }
}

void CCD::sendImg() const {
    const int32_t head[7]{0, N, N, 1, 24, 0x7F800000, 0x7F800000};
    Serial.write((const char*)head, sizeof(head));
    Serial.write((const char*)data, sizeof(data));
    Serial.flush();
}