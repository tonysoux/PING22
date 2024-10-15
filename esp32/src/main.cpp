#include "PING.hpp"

void setup() 
{
    Serial.begin(115200);
    PING::setup();

}

void loop()
{
    Serial.println(PING::player1.beamSwitch.getState());
    delay(100);
}