#include "./OilPressureReader.hpp"

OilPressureReader::OilPressureReader(byte pin){
    resistanceReader = new ResistanceReader(pin, R1);
}

float OilPressureReader::getOilPressurePsi(){
    float r = resistanceReader->getResistance();
    return (1.3071*r)-28.47878; //based on readings for my sensor. Subject to change
}