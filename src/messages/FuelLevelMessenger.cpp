#include "./FuelLevelMessenger.hpp"

FuelLevelMessenger::FuelLevelMessenger(Priority priority, VpwOut* vpwOut): IMessenger(priority, vpwOut){
      fuelLevelReader = new FuelLevelReader(fuelLevelPin);
      this->vpwOut = vpwOut;
}

void FuelLevelMessenger::SendMessage(){
      float fuelLevelPercentage = fuelLevelReader->getFuelLevelPercentage();
      byte fuelLevel = fuelLevelPercentage*0.01*255;
      const byte fuelLevelMessage[2] = {0xA4, fuelLevel};
      vpwOut->sendMessage(fuelLevelMessage, 2);
}