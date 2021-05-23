#include "./RPMandMPHMessenger.hpp"
#include "../sensors/abstract/PulseReader.hpp"

RPMandMPHMessenger::RPMandMPHMessenger(Priority priority, VpwOut* vpwOut, BusDataReader* busDataReader): IMessenger(priority, vpwOut){    
    this->busDataReader = busDataReader;
}

void RPMandMPHMessenger::SendMessage(){
    const int rpmScaled = busDataReader->getRpm()*4;
    const int mphScaled = busDataReader->getMph()*215;
    //v-- Refactor this --v
    byte rpmBytes[2];
    rpmBytes[0]=((rpmScaled)>>8)&0xFF;
    rpmBytes[1]=(rpmScaled)&0xFF;
    byte mphBytes[2];
    mphBytes[0]=((mphScaled)>>8)&0xFF;
    mphBytes[1]=(mphScaled)&0xFF;
    //^-- Refactor this --^
    
    const byte rpmMessage[6] = {0x10, rpmBytes[0], rpmBytes[1], mphBytes[0], mphBytes[1], 0x3A}; //Last byte is manifold air pressure. Dash probably doesn't care about this.
    vpwOut->sendMessage(rpmMessage, 6);
}