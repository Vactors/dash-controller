#include "./VpwOut.hpp"

VpwOut::VpwOut(byte transmitPin, byte receivePin, int timeoutMs, VpwIn *vpwIn){
    this->transmitPin = transmitPin;
    this->receivePin = receivePin;
    pinMode(receivePin, INPUT);
    pinMode(transmitPin, OUTPUT);
    digitalWrite(transmitPin, HIGH);
    this->timeoutMicros = timeoutMs*1000; // convert to microseconds
    this->vpwIn = vpwIn;
}

void VpwOut::sendMessage(const byte *pData, byte nBytes)
{   
    //Should add error response here. May also not handle overflows gracefully
    const byte msgLength = nBytes + 1; // 1 byte crc
    byte buff[msgLength];
    memcpy(buff, pData, nBytes);
    buff[msgLength - 1] = crc(buff, nBytes);

    // for (int i=0; i<msgLength; i++){
    //     Serial.print(buff[i], HEX);
    // }
    // Serial.println();

    // wait for idle
    unsigned long lastBusActive = micros();
    unsigned long start = lastBusActive;
    while (micros() - lastBusActive < TX_EOF)
    {
        if (digitalRead(receivePin) == LOW)
        {
            lastBusActive = micros();
        }

        if (micros() - start > timeoutMicros)
        {
            Serial.println("timeout");
            return;
        }
    }
    //this->vpwIn->suspendListening(); //Timing sensitive, need to suspend interrupts momentarilly. May not need this when GM and Dodge bus use separate wires
    unsigned long pulseTimer;
    // SOF
    digitalWrite(transmitPin, LOW);
    pulseTimer = micros();
    while (micros() - pulseTimer < TX_SOF)
        ;

    byte currentByte = 0;
    while (currentByte < msgLength)
    {
        byte nbits = 8;
        unsigned long transmitTime;
        while (nbits--)
        {
            if (nbits & 0x1)
            { //Alternate between passive and active transmission
                transmitTime = (buff[currentByte] & 0x80) ? TX_LONG : TX_SHORT;
                digitalWrite(transmitPin, HIGH);
                pulseTimer = micros();
                while (micros() - pulseTimer < transmitTime)
                {
                    if (digitalRead(receivePin) == LOW)
                    { //Arbitration has been lost. We're telling the bus to go low but it's high.
                        //this->vpwIn->resumeListening();
                        Serial.println("High arbitration lost");
                        return;
                    }
                }
            }
            else
            {
                transmitTime = (buff[currentByte] & 0x80) ? TX_SHORT : TX_LONG;
                digitalWrite(transmitPin, LOW);
                pulseTimer = micros();
                while (micros() - pulseTimer < transmitTime)
                    ;
            }
            buff[currentByte] <<= 1;
        }
        currentByte++;
    }
    digitalWrite(transmitPin, HIGH);
    pulseTimer = micros();
    while (micros() - pulseTimer < TX_EOF)
    {
        if (digitalRead(receivePin) == LOW)
        { //Arbitration has been lost. We're telling the bus to go high but it's low.
            //this->vpwIn->resumeListening();
            Serial.println("High arbitration lost");
            return;
        }
    }
    //this->vpwIn->resumeListening();
}

byte VpwOut::crc(byte *msg_buf, byte nbytes){
        byte crc_reg = 0xff, poly, byte_count, bit_count;
        byte *byte_point;
        byte bit_point;
    
        for (byte_count = 0, byte_point = msg_buf; byte_count < nbytes; ++byte_count, ++byte_point)
        {
            for (bit_count = 0, bit_point = 0x80; bit_count < 8; ++bit_count, bit_point >>= 1)
            {
                if (bit_point & *byte_point) // case for new bit = 1
                {
                    if (crc_reg & 0x80)
                        poly = 1; // define the polynomial
                    else
                        poly = 0x1c;
                    crc_reg = ((crc_reg << 1) | 1) ^ poly;
                }
                else // case for new bit = 0
                {
                    poly = 0;
                    if (crc_reg & 0x80)
                        poly = 0x1d;
                    crc_reg = (crc_reg << 1) ^ poly;
                }
            }
        }
        return ~crc_reg; // Return CRC
    }