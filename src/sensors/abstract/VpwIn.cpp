#include "./VpwIn.hpp"

VpwIn::VpwIn(byte pin){
    this->pin = pin;
    q = new Queue(messageLength, 100, FIFO, true);
    memset(buff, 0, sizeof(buff));
}

void VpwIn::attachCallback(void (*dataCallback)(void)){
    this->dataCallback = dataCallback;
    pinMode(pin, INPUT);
    resumeListening();
}

byte* VpwIn::getMostRecentMessage(){
    static byte outMsg[messageLength];
    if (q->pop(outMsg)){
        return outMsg;
    } else {
        return NULL;
    }
}

boolean VpwIn::hasMessages(){
    static byte outMsg[messageLength];
    return q->peek(outMsg);
}

void VpwIn::printMostRecentMessage(){
    const byte* msg = getMostRecentMessage();
    if(msg && msg[2] == 0x10){
        char tmp[messageLength*2+1];
        byte first;
        byte second;
        for (int i=0; i<messageLength; i++) {
            first = (msg[i] >> 4) & 0x0f;
            second = msg[i] & 0x0f;
            // base for converting single digit numbers to ASCII is 48
            // base for 10-16 to become lower-case characters a-f is 87
            // note: difference is 39
            tmp[i*2] = first+48;
            tmp[i*2+1] = second+48;
            if (first > 9) tmp[i*2] += 39;
            if (second > 9) tmp[i*2+1] += 39;
        }
        tmp[messageLength*2] = 0;
        Serial.println(tmp); 
    }
}

void VpwIn::suspendListening(){
    detachInterrupt(digitalPinToInterrupt(pin));
}

void VpwIn::resumeListening(){
    bitMarker = 0;
    msgBuf = buff;
    inFrame = false;
    pinState = digitalRead(pin);
    lastTime = micros();
    attachInterrupt(digitalPinToInterrupt(pin), dataCallback, CHANGE);
}

void VpwIn::recordPulseTiming(){
    unsigned long now = micros();
    unsigned long diff;

    if (now < lastTime)
    {
        // overflow occured
        diff = now + (MAX_uS - lastTime);
    }
    else
    {
        diff = now - lastTime;
    }

    lastTime = now;

    if (!inFrame)
    {
        if (pinState == LOW && IsBetween(diff, RX_SOF_MIN, RX_SOF_MAX))
        {
            inFrame = true;
            bitMarker = 0;
            msgBuf = buff;
            *msgBuf = 0;
        }
    // Need to handle invalid pulse properly here
    }else{
        *msgBuf <<= 1;
        bitMarker++;
        if (pinState == HIGH){
            if (diff > RX_EOF_MIN)
            {
                // data ended - copy package to buffer
                inFrame = false; 
                onFrameRead();
                pinState = digitalRead(pin);
                return;
            }
            if (IsBetween(diff, RX_LONG_MIN, RX_LONG_MAX))
            {
                *msgBuf |= 1;
            }
        }else if (IsBetween(diff, RX_SHORT_MIN, RX_SHORT_MAX)){
            *msgBuf |= 1;
        }
        if (bitMarker == 8){
            msgBuf++;
            *msgBuf = 0;
            bitMarker = 0;
        } 
    }
    pinState = digitalRead(pin);
}

bool VpwIn::IsBetween(unsigned long x, unsigned long min, unsigned long max){
    return (x >= min && x <= max);
}

void VpwIn::onFrameRead(){
    q->push(buff);
    memset(buff, 0, sizeof(buff));
}