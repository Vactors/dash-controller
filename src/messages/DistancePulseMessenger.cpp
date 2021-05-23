#include "DistancePulseMessenger.hpp"

DistancePulseMessenger::DistancePulseMessenger(Priority priority, VpwOut* vpwOut): IMessenger(priority, vpwOut){
}

void DistancePulseMessenger::SendMessage()
{
    byte distancePulseMessage[6] = {0x5D, 0x00, 0x00, 0x00, 0x00, 0x00};
    vpwOut->sendMessage(distancePulseMessage, 6);
}