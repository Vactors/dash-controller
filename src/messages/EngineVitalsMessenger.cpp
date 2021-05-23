#include "./EngineVitalsMessenger.hpp"

EngineVitalsMessenger::EngineVitalsMessenger(Priority priority, VpwOut* vpwOut, BusDataReader* busDataReader) : IMessenger(priority, vpwOut){
    this->busDataReader = busDataReader;
    oilPressureReader = new OilPressureReader(oilPressurePin);
    batteryVoltageReader = new BatteryVoltageReader(voltagePin);
}

void EngineVitalsMessenger::SendMessage(){
    float voltage = batteryVoltageReader->getBatteryVoltage();
    byte voltageByte = (int)(voltage*16.0);
    byte coolantTemp = busDataReader->getCoolantTempByte();
    float oilPressurePsi = oilPressureReader->getOilPressurePsi();
    int scaledOilPressure = (int)(oilPressurePsi*(96.0/55.0))-3;
    if (scaledOilPressure < 0){
        scaledOilPressure = 0;
    }
    byte oilPressureByte = scaledOilPressure;
    const byte engineVitalsMessage[5] = {0xC0, voltageByte, oilPressureByte, coolantTemp, 0x80};
    vpwOut->sendMessage(engineVitalsMessage, 5);
}