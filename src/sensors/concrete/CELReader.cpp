#include "./CELReader.hpp"

CELReader::CELReader(byte pin){
    groundReader = new GroundReader(pin);
}

bool CELReader::isCELEnabled(){
    return groundReader->isGrounded();
}