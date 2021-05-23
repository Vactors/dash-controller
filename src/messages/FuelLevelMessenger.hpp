#pragma once

#include "./IMessenger.hpp"
#include "./VpwOut.hpp"
#include "../sensors/concrete/FuelLevelReader.hpp"

class FuelLevelMessenger: public IMessenger{
    public:
        FuelLevelMessenger(Priority priority, VpwOut* vpwOut);
        void SendMessage() override;
    private:
        FuelLevelReader* fuelLevelReader;
        static const byte fuelLevelPin = A1;
};