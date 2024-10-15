#include "Player.hpp"

Player::Player(int stepPin, int dirPin, int rxPin, int solenoidPin, int beamSwitchRPin) : actuator(stepPin, dirPin, rxPin), solenoid(solenoidPin), beamSwitch(beamSwitchRPin)
{
}

Player::~Player()
{
}

int Player::setup()
{
    beamSwitch.setup();
    return 0;
}

int Player::loop()
{
    beamSwitch.check();
    // Serial.println(beamSwitch.);
    return 0;
}