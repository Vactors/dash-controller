#pragma once
#include <Arduino.h>
#include <limits.h>
#include <cppQueue.h>

class VpwIn{
    private:
        static const unsigned long MAX_uS = ULONG_MAX;

        static const unsigned long RX_SOF_MIN = 163;
        static const unsigned long RX_SOF_MAX = 239;
        
        static const unsigned int RX_EOF_MIN = 239; // minimum end of data time
        
        static const unsigned int RX_SHORT_MIN = 34; // minimum short pulse time
        static const unsigned int RX_SHORT_MAX = 96; // maximum short pulse time
        
        static const unsigned int RX_LONG_MIN = 97;  // minimum long pulse time
        static const unsigned int RX_LONG_MAX = 163; // maximum long pulse time

        static const byte messageLength = 9;

        void (*dataCallback)(void);
        byte pin;
        volatile bool pinState;
        volatile unsigned long lastTime;
        volatile bool inFrame;
        byte buff[messageLength]; //May need to be volatile
        volatile byte *msgBuf;
        volatile byte bitMarker;
        Queue *q;

        bool IsBetween(unsigned long x, unsigned long min, unsigned long max);
        void onFrameRead();
    
    public:
        VpwIn(byte pin);
        void attachCallback(void (*dataCallback)(void));
        byte* getMostRecentMessage();
        void printMostRecentMessage();
        void suspendListening();
        void resumeListening();
        void recordPulseTiming();
        bool hasMessages();
};