#include "IMessenger.hpp"

IMessenger::IMessenger(Priority priority, VpwOut* vpwOut){
    this->priority = priority;
    this->vpwOut = vpwOut;
}

Priority IMessenger::GetPriority(){
    return priority;
}