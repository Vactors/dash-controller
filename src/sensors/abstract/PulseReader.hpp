#pragma once
#include <Arduino.h>

class PulseReader {
    private:
        byte pin;
        volatile int pulseCount;
        volatile float lastPulseTimeStamp;
        volatile float timeSinceLastPulse;
    public:
        PulseReader(byte pin);
        void attachCallback(void (*ISR_callback)(void));
        int getPulses();
        void handleInterrupt();
        float getPulsePeriod();
};