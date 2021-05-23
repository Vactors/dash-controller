#pragma once
#include <Arduino.h>
#include "./sensors/concrete/BusDataReader.hpp"
#include "./messages/IMessenger.hpp"
#include "./messages/VpwOut.hpp"
#include "./sensors/abstract/VpwIn.hpp"

class DashController
{
    private:
        unsigned long lastSendTimestamp;
        const unsigned long messageDelayus = 50000;
        void printData();
        BusDataReader *busDataReader;
        VpwOut *vpwOut;
        static const byte vpwInPin = 2;
        static const byte vpwOutTx = 5;
        static const byte vpwOutRx = 6;
        static const int numMessengers = 6;
        IMessenger* messengers[numMessengers];
        int loopCount = 0;

    public:
        DashController();
        void tick();
};