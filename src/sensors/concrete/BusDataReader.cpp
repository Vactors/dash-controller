#include "./BusDataReader.hpp"

BusDataReader::BusDataReader(VpwIn* vpwReader){
    this->vpwReader = vpwReader;
    coolantTempByte = 0x0;
    prndl = 0x01;
    mph = 0;
    rpm = 0;
}

byte* BusDataReader::getLastMessage(){
    return vpwReader->getMostRecentMessage();
}

void BusDataReader::updateDiag(){
    //Should probably memcpy
    byte* lastMessage = vpwReader->getMostRecentMessage();
    if(lastMessage){
        lastMessageTimestamp = millis();
        if(lastMessage[1] == 0x49 && lastMessage[3] == 0x10){
            coolantTempByte = lastMessage[4];
        }
        if(lastMessage[1] == 0xea){
            if(lastMessage[3] == 0x0a){
                prndl = lastMessage[4];
            }
        }
        if(lastMessage[1] == 0x1b && lastMessage[3] == 0x10){
            rpm = (256*lastMessage[4]+lastMessage[5])/4;
        }
        if(lastMessage[1] == 0x29 && lastMessage[3] == 0x01){
            mph = lastMessage[4];
        }
    }
}

byte BusDataReader::getCoolantTempByte(){
    return coolantTempByte;
}

float BusDataReader::getCoolantTemp(){
    return (coolantTempByte-40.0)*1.8 + 32;
}

const byte BusDataReader::getRangeSelectionByte(){
    return prndl;
}

const char* BusDataReader::getRangeSelection(){
    switch(prndl) {
    case 0x01 :
        return "Park";
    case 0x02 :
        return "Reverse";
    case 0x03 :
        return "Neutral";
    case 0x09 :
        return "Drive";
    case 0x08 :
        return "3";
    case 0x07 :
        return "2";
    case 0x06 :
        return "1";
    default :
        return "Unknown";
    }
}

int BusDataReader::getMph(){
    return mph;
}

int BusDataReader::getRpm(){
    return rpm;
}

bool BusDataReader::isBusActive(){
    if(vpwReader->hasMessages() || millis() - lastMessageTimestamp < busTimeout){
        return true;
    }else{
        return false;
    }
}