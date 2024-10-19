#ifndef LINEARACTUATOR_HPP
#define LINEARACTUATOR_HPP
#include <TMCStepper.h>
#include <AccelStepper.h>
#include "config.h"

#define MICRO_STEPS_PER_MM (float)STEPS_PER_REVOLUTION * POULLEY_TEETH / BELT_PITCH / (1 << MICROSTEP_POWER_OF_2)

class LinearActuator
{
private:
    int rightLimit = INT_MAX;
    int leftLimit = INT_MIN;
    TMC2209Stepper driver;
    AccelStepper motor;

public:
    LinearActuator(int stepPin, int dirPin, int address);
    ~LinearActuator();
    void setup();
    bool calibrateRight();
    bool calibrateLeft(); 
    void setSpeed(float speed);
    void setAcceleration(float acceleration);
    void moveTo(float position);
    void moveRight();
    void moveLeft();
    void stop();
    void run();
};

#endif