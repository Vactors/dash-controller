#include "VinMessenger.hpp"

VinMessenger::VinMessenger(Priority priority, VpwOut* vpwOut): IMessenger(priority, vpwOut){
}

void VinMessenger::SendMessage()
{
    // // Definitely a better way to do this. This is quicker.
    // // byte 1 (F0) is the vin address, byte 2 is what part of the vin is in the payload
    // byte vinMessage1[3] = {0xF0, 0x01, vin[0]};
    // byte vinMessage2[6] = {0xF0, 0x02, vin[1], vin[2], vin[3], vin[4]};
    // byte vinMessage3[6] = {0xF0, 0x06, vin[5], vin[6], vin[7], vin[8]};
    // byte vinMessage4[6] = {0xF0, 0x0A, vin[9], vin[10], vin[11], vin[12]};
    // byte vinMessage5[6] = {0xF0, 0x0E, vin[13], vin[14], vin[15], vin[16]};
    
    // vpwOut->sendMessage(vinMessage1, 3);
    // vpwOut->sendMessage(vinMessage2, 6);
    // vpwOut->sendMessage(vinMessage3, 6);
    // vpwOut->sendMessage(vinMessage4, 6);
    // vpwOut->sendMessage(vinMessage5, 6);
}