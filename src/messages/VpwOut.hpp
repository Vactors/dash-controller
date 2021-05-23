#pragma once
#pragma once

#include "../sensors/abstract/VpwIn.hpp"

class VpwOut
{
    private:
        byte transmitPin;
        byte receivePin;
        int timeoutMicros;
        VpwIn *vpwIn;
        static const unsigned int TX_SHORT = 64; // Short pulse nominal time
        static const unsigned int TX_LONG = 128; // Long pulse nominal time
        static const unsigned int TX_SOF = 200;  // Start Of Frame nominal time
        static const unsigned int TX_EOD = 200;  // End Of Data nominal time
        static const unsigned int TX_EOF = 280;  // End Of Frame nominal time

        byte crc(byte *msg_buf, byte nbytes);

    public:
        VpwOut(byte transmitPin, byte receivePin, int timeoutMs, VpwIn *vpwIn);
        void sendMessage(const byte *pData, byte nBytes);
};