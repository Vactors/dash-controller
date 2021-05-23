#pragma once

#include <Arduino.h>

class GroundReader
{
    private:
        byte pin;

    public:
        GroundReader(byte pin);
        bool isGrounded();
};