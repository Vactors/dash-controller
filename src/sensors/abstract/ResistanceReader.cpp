#include "./ResistanceReader.hpp"

ResistanceReader::ResistanceReader(byte pin, int r1) {
      this->pin = pin;
      this->r1 = r1;
}

float ResistanceReader::getResistance() {
    int raw = analogRead(pin);
    float vOut = raw * (vIn / 1023.0);
    if (raw) {
        float r2 = (r1*vOut)/(vIn-vOut);
        return r2;
    }
}