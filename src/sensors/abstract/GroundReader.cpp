#include "./GroundReader.hpp"

GroundReader::GroundReader(byte pin){
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
};

bool GroundReader::isGrounded(){
    return !digitalRead(pin); //inverse to get ground state
}