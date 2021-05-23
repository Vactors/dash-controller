#pragma once

#include "../abstract/ResistanceReader.hpp"

class OilPressureReader{
    private:
        const int R1 = 510;
        ResistanceReader* resistanceReader;
    public:
        OilPressureReader(byte pin);
        float getOilPressurePsi();
};