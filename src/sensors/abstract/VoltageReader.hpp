#pragma once
#include <Arduino.h>

class VoltageReader {
    private:
        byte pin;
        float r1;
        float r2;
        const int vIn = 5;
    public:
        VoltageReader(byte pin, long r1, long r2);
        float getVoltage();
};