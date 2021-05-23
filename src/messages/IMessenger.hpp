#pragma once

#include "./Priority.hpp"
#include "./VpwOut.hpp"

class IMessenger
{
    protected:
        Priority priority;
        VpwOut* vpwOut;
    public:
        IMessenger(Priority priority, VpwOut* vpwOut);
        virtual void SendMessage() = 0;
        Priority GetPriority();
};