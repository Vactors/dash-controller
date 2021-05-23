#pragma once

#include "./IMessenger.hpp"
#include "./VpwOut.hpp"

class VinMessenger: public IMessenger{
    public:
        VinMessenger(Priority priority, VpwOut* vpwOut);
        void SendMessage() override;
    private:
        const byte vin[17] = {'1','B','7','G','G','3','2','N','4','2','S','5','0','9','1','6','4'};
};