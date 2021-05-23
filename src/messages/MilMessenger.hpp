#pragma once

#include "./IMessenger.hpp"
#include "./VpwOut.hpp"
#include "../sensors/concrete/CELReader.hpp"

class MilMessenger: public IMessenger{
    public:
        MilMessenger(Priority priority, VpwOut* vpwOut);
        void SendMessage() override;
    private:
        CELReader* milReader;
        static const byte celPin = 4;
};