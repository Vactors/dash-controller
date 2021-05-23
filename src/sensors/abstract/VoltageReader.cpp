#include "./VoltageReader.hpp"

VoltageReader::VoltageReader(byte pin, long r1, long r2){
    this->pin = pin;
    this->r1 = r1;
    this->r2 = r2;
}

float VoltageReader::getVoltage(){
    int raw = analogRead(pin);
    if(raw){
        float volts = raw * (vIn / 1023.0);
        return (volts*(r1+r2))/r2;
    }
}