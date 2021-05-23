#pragma once

#include "./IMessenger.hpp"
#include "./VpwOut.hpp"

class DistancePulseMessenger: public IMessenger{
    public:
        DistancePulseMessenger(Priority priority, VpwOut* vpwOut);
        void SendMessage() override;
};