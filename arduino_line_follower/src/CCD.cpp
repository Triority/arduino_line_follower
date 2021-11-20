#include "CCD.hpp"

#include <Arduino.h>
#include <float.h>

void CCD::init() const {
    pinMode(CLK, OUTPUT);
    pinMode(SI, OUTPUT);
    pinMode(AO, INPUT);
}

void CCD::collect() {
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
    const int M = 10;

    int16_t peak = 0, pi = 0;
    int32_t sum = 0;

    for (int i = M; i < N - M; ++i) {
        sum += data[i];
        int16_t cur = data[i - M] + data[i + M] - (data[i] << 1);
        if (cur > peak) peak = cur, pi = i;
    }

    _avg = sum / (N - 2 * M);

    _s2 = 0;
    for (int i = M; i < N - M; ++i) { _s2 += (data[i] - _avg) * (data[i] - _avg); }

    isValid = _s2 > thresh;
    if (isValid) _res = pi;
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