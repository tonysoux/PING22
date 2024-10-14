#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "LinearActuator.hpp"
#include "Solenoid.hpp"
#include "BeamSwitchDetector.hpp"

class Player
{
private:
    LinearActuator *actuator;
    Solenoid *solenoid;
    BeamSwitchDetector *beamSwitch;
public:
    Player(int stepPin, int dirPin, int rxPin, int solenoidPin, int beamSwitchTPin, int beamSwitchRPin);
    int loop();
    ~Player();
};

Player::Player(int stepPin, int dirPin, int rxPin, int solenoidPin, int beamSwitchTPin, int beamSwitchRPin)
{
    actuator = new LinearActuator(stepPin, dirPin, rxPin);
    solenoid = new Solenoid(solenoidPin);
    beamSwitch = new BeamSwitchDetector(beamSwitchTPin, beamSwitchRPin);
}

Player::~Player()
{
}


int Player::loop()
{
    // actuator->loop();
    // solenoid->loop();
    beamSwitch->loop();
    return 0;
}

#endif
