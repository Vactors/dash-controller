#include "./DashController.hpp"
#include "./messages/EngineVitalsMessenger.hpp"
#include "./messages/FuelLevelMessenger.hpp"
#include "./messages/RPMandMPHMessenger.hpp"
#include "./messages/MilMessenger.hpp"
#include "./messages/VinMessenger.hpp"
#include "./messages/SelectedRangeMessenger.hpp"
#include "./messages/DistancePulseMessenger.hpp"

DashController::DashController(){
    static VpwIn* vpwIn = new VpwIn(vpwInPin);
    vpwIn->attachCallback([]{vpwIn->recordPulseTiming();});
    vpwOut = new VpwOut(vpwOutTx, vpwOutRx, 500, vpwIn);
    busDataReader = new BusDataReader(vpwIn);
    messengers[0] = new EngineVitalsMessenger(PRIORITY_3, vpwOut, busDataReader);
    messengers[1] = new FuelLevelMessenger(MAX_PRIORITY, vpwOut);
    messengers[2] = new RPMandMPHMessenger(PRIORITY_0, vpwOut, busDataReader);
    messengers[3] = new SelectedRangeMessenger(PRIORITY_0, vpwOut, busDataReader);
    messengers[4] = new MilMessenger(PRIORITY_3, vpwOut);
    messengers[5] = new DistancePulseMessenger(PRIORITY_3, vpwOut);
}

void DashController::tick(){
    if (busDataReader->isBusActive()){
        if (loopCount > MAX_PRIORITY){
            loopCount = 1;
        }
        for (int i=0; i<numMessengers; i++){
            if(loopCount % messengers[i]->GetPriority() == 0){
                messengers[i]->SendMessage();
                lastSendTimestamp = micros();
                while(micros() - lastSendTimestamp < messageDelayus){
                    busDataReader->updateDiag();
                }
            }
        }
        loopCount++;
    }
}

// void DashController::printData(){
//     float coolantTemp = engineDiag->getCoolantTemp();
//     float oilPressure = engineDiag->getOilPressurePsi();
//     float voltage = engineDiag->getVoltage();
//     float fuelLevel = engineDiag->getFuelLevelPercentage();
//     float rpm = engineDiag->getRpm();
//     float mph = engineDiag->getMph();
//     bool celEnabled = engineDiag->isCelOn();
//     const char* selectedRange = engineDiag->getRangeSelection();
//     Serial.print("Battery Voltage (v): ");
//     Serial.print(voltage);
//     Serial.print("   Oil Pressure (PSI): ");
//     Serial.print(oilPressure);
//     Serial.print("   Fuel Level (%): ");
//     Serial.print(fuelLevel);
//     Serial.print("   Rpm: ");
//     Serial.print(rpm);
//     Serial.print("   Mph: ");
//     Serial.print(mph);
//     Serial.print("   Coolant Temp (F): ");
//     Serial.print(coolantTemp);
//     Serial.print("   Selected Range: ");
//     Serial.print(selectedRange);
//     Serial.print("   CEL on: ");
//     Serial.println(celEnabled ? "yes" : "no");
// }