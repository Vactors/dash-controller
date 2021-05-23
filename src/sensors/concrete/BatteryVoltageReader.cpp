#include "./BatteryVoltageReader.hpp"

BatteryVoltageReader::BatteryVoltageReader(byte pin){
    voltageReader = new VoltageReader(pin, voltageR1, voltageR2);
}

float BatteryVoltageReader::getBatteryVoltage(){
    return voltageReader->getVoltage(); 
}