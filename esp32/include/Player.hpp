#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "LinearActuator.hpp"
#include "Solenoid.hpp"
#include "BeamSwitchDetector.hpp"

class Player
{
public:
    LinearActuator actuator;
    Solenoid solenoid;
    BeamSwitchDetector beamSwitch;
public:
    Player(int stepPin, int dirPin, int rxPin, int solenoidPin, int beamSwitchRPin);
    int setup();
    int loop();
    ~Player();
};

#endif