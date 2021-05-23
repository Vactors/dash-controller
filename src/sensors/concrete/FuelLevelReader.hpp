#pragma once

#include "../abstract/ResistanceReader.hpp"
#include "../../util/movingAvg.h"

class FuelLevelReader{
    private:
        const int R1 = 510;
        ResistanceReader* resistanceReader;
        movingAvg* movingAverage;
    public:
        FuelLevelReader(byte pin);
        float getFuelLevelPercentage();
};