#include "SelectedRangeMessenger.hpp"

SelectedRangeMessenger::SelectedRangeMessenger(Priority priority, VpwOut* vpwOut, BusDataReader* busDataReader): IMessenger(priority, vpwOut){    
    this->busDataReader = busDataReader;
}

void SelectedRangeMessenger::SendMessage(){
    //0x01=P, 0x02=R, 0x03=N, 0x05=D, 0x06=2, 0x07=1
    byte rangeByte = busDataReader->getRangeSelectionByte();
    byte convertedRangeByte;
    switch(rangeByte){
        case 0x01 :
            convertedRangeByte = 0x01;
            break;
        case 0x02 :
            convertedRangeByte = 0x02;
            break;
        case 0x03 :
            convertedRangeByte = 0x03;
            break;
        case 0x09 :
            convertedRangeByte = 0x05;
            break;
        case 0x08 :
            convertedRangeByte = 0x05; // Turn the OD off light on when in manual 3rd
            break;
        case 0x07 :
            convertedRangeByte = 0x06;
            break;
        case 0x06 :
            convertedRangeByte = 0x07;
            break;
        default :
            return;
    }
    byte rangeMessage[3] = {0x37, convertedRangeByte, 0x00};
    vpwOut->sendMessage(rangeMessage, 3);
}