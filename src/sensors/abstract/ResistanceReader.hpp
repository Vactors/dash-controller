#pragma once
#include <Arduino.h>

class ResistanceReader {
    private:
        byte pin;
        float r1;
        const int vIn = 5;
    public:
        ResistanceReader(byte pin, int r1);
        float getResistance();
};