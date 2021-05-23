#pragma once

#include "./IMessenger.hpp"
#include "./VpwOut.hpp"
#include "../sensors/concrete/MphReader.hpp"
#include "../sensors/concrete/RpmReader.hpp"
#include "../sensors/concrete/BusDataReader.hpp"

class RPMandMPHMessenger: public IMessenger{
    public:
        RPMandMPHMessenger(Priority priority, VpwOut* vpwOut, BusDataReader* busDataReader);
        void SendMessage() override;
    private:
        static const byte RPMInterruptPin = 19;
        static const byte MPHInterruptPin = 18;
        MphReader* mphReader;
        RpmReader* rpmReader;
        BusDataReader* busDataReader;
};