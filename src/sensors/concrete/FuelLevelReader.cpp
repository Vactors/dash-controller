#include "./FuelLevelReader.hpp"

FuelLevelReader::FuelLevelReader(byte pin){
    resistanceReader = new ResistanceReader(pin, R1);
    movingAverage = new movingAvg(10);
    movingAverage->begin();
}

float FuelLevelReader::getFuelLevelPercentage(){
    float r = resistanceReader->getResistance();
    movingAverage->reading(r);
    int avg = movingAverage->getAvg();
    return -avg/2 + 110;
}