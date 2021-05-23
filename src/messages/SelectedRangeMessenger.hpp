#pragma once

#include "./IMessenger.hpp"
#include "./VpwOut.hpp"
#include "../sensors/concrete/BusDataReader.hpp"

class SelectedRangeMessenger: public IMessenger{
    public:
        SelectedRangeMessenger(Priority priority, VpwOut* vpwOut, BusDataReader* busDataReader);
        void SendMessage() override;
    private:
        BusDataReader* busDataReader;
};