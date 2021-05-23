#pragma once

#include <Arduino.h>
#include "../abstract/VpwIn.hpp"

class BusDataReader{
    private:
        byte coolantTempByte;
        byte prndl;
        VpwIn* vpwReader;
        int rpm;
        int mph;
        unsigned long lastMessageTimestamp;
        const unsigned long busTimeout = 3000; //3 seconds without bus activity means the pcm is probably powered down.
    public:
        BusDataReader(VpwIn* vpwReader);
        byte* getLastMessage();
        void updateDiag();
        byte getCoolantTempByte();
        float getCoolantTemp();
        const byte getRangeSelectionByte();
        const char* getRangeSelection();
        int getRpm();
        int getMph();
        bool isBusActive();
};