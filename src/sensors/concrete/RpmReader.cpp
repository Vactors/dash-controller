#include "./RpmReader.hpp"
#include "../abstract/PulseReader.hpp"

RpmReader::RpmReader(PulseReader* pulseReader){
    this->pulseReader = pulseReader;
}

float RpmReader::getRpm(){
    float period = pulseReader->getPulsePeriod();
    float pulsesPerMinute = (60)/(period);
    //crank signal is 2 pulses per rotation
    return pulsesPerMinute/2.0;
}