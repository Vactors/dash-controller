#pragma once
#include <Arduino.h>
#include "../abstract/VoltageReader.hpp"

class BatteryVoltageReader{
    private:
        static const long voltageR1 = 1000000;
        static const long voltageR2 = 100000;
        VoltageReader* voltageReader; 
    public:
        BatteryVoltageReader(byte pin);
        float getBatteryVoltage();
};