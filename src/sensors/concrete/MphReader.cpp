#include "./MphReader.hpp"
#include "../abstract/PulseReader.hpp"

MphReader::MphReader(PulseReader* pulseReader){
    this->pulseReader = pulseReader;
}

float MphReader::getMph(){
    float period = pulseReader->getPulsePeriod();
    float pulsesPerHour = (60.0*60.0)/(period);
    //vss is 4k ppm
    return pulsesPerHour/4000;
}