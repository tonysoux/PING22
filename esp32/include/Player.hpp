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

#endif
