#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "LinearActuator.hpp"
#include "Solenoid.hpp"
#include "BeamSwitch.hpp"

class Player
{
public:
    LinearActuator actuator;
    Solenoid solenoid;
    BeamSwitch beamSwitch;
public:
    Player(int stepPin, int dirPin, int address, int solenoidPin, int beamSwitchRPin);
    int setup();
    int loop();
    ~Player();
};

#endif