#pragma once

#include "../abstract/PulseReader.hpp"

class RpmReader {
    private:
        unsigned long lastTime;
        PulseReader* pulseReader;
    public:
        RpmReader(PulseReader* pulseReader);
        float getRpm();
};