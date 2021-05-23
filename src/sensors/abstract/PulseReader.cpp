#include "./PulseReader.hpp"

PulseReader::PulseReader(byte pin){
    this->pin = pin;
    pulseCount = 0;
    lastPulseTimeStamp = micros();
    timeSinceLastPulse = 0;
}

void PulseReader::attachCallback(void (*ISR_callback)(void)){
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), ISR_callback, FALLING);
}

int PulseReader::getPulses() { // Change this to use period
    int countSinceLastReset = pulseCount;
    pulseCount = 0;
    return countSinceLastReset;
}

void PulseReader::handleInterrupt() {
    pulseCount++;
    float now = micros();
    timeSinceLastPulse = now - lastPulseTimeStamp;
    lastPulseTimeStamp = now;
}

float PulseReader::getPulsePeriod(){
    return timeSinceLastPulse/1000000.0;//Convert to pulses per second (hZ)
}