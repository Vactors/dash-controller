#include "MilMessenger.hpp"

MilMessenger::MilMessenger(Priority priority, VpwOut* vpwOut): IMessenger(priority, vpwOut){
    milReader = new CELReader(celPin);
}

void MilMessenger::SendMessage(){
    const byte milOffMessage[4] = {0xB0, 0x00, 0x00, 0x00}; //Spoofing mil off state. Connect to GM pcm when dtc's are deleted (evap, secondary o2s, etc.)
    const byte milOnMessage[4] = {0xB0, 0x80, 0x00, 0x00};
    const byte absMessage[4] = {0x63, 0x00, 0x00};
    const byte service4wdMessage[4] = {0x92, 0x07, 0x00};
    if(milReader->isCELEnabled()){
        vpwOut->sendMessage(milOnMessage, 4);
    }else{
        vpwOut->sendMessage(milOffMessage, 4);
    }
    
    vpwOut->sendMessage(absMessage, 3);
    vpwOut->sendMessage(service4wdMessage, 3);
}