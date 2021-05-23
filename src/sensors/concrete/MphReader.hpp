#pragma once

#include "../abstract/PulseReader.hpp"

class MphReader {
    private:
        unsigned long lastTime;
        PulseReader* pulseReader;
    public:
        MphReader(PulseReader* pulseReader);
        float getMph();
};