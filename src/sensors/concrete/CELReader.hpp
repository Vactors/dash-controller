#pragma once

#include "../abstract/GroundReader.hpp"

class CELReader{
    private:
        GroundReader* groundReader;
    public:
        CELReader(byte pin);
        bool isCELEnabled();
};