#include "CCD.hpp"

#include <Arduino.h>

void CCD::init() {
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

void CCD::send() {
    Serial.write("\x00\xff\x01\x00", 4);
    for (int i = 0; i < N; ++i) {
        Serial.write(data[i] >> 8);
        Serial.write(data[i] & 0XFF);
    }
}
