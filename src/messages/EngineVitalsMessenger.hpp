#pragma once

#include "./IMessenger.hpp"
#include "../sensors/concrete/BusDataReader.hpp"
#include "../sensors/concrete/BatteryVoltageReader.hpp"
#include "../sensors/concrete/OilPressureReader.hpp"

class EngineVitalsMessenger: public IMessenger{
    public:
        EngineVitalsMessenger(Priority priority, VpwOut* vpwOut, BusDataReader* busDataReader);
        void SendMessage() override;
    private:
        static const byte oilPressurePin = A4;
        static const byte voltagePin = A2;
        BusDataReader* busDataReader;
        OilPressureReader* oilPressureReader;
        BatteryVoltageReader* batteryVoltageReader;
};