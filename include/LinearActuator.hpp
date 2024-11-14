#ifndef LINEAR_ACTUATOR_HPP
#define LINEAR_ACTUATOR_HPP
#include <AccelStepper.h>
#include <TMCStepper.h>
#include "config.h"

#define MICRO_STEPS_PER_MM (float)STEPS_PER_REVOLUTION / PULLEY_TEETH / BELT_PITCH * (1 << MICROSTEP_POWER_OF_2)
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define saturate(a, low, high) (min(max(a, low), high))

namespace RunStatus
{
    enum Status
    {
        IDLE,
        RUNNING,
        COLLISION
    };
}

class LinearActuator
{
public:
    static void setup_Serial() { TMC_SERIAL_PORT.begin(TMC_SERIAL_BAUD_RATE); }
    LinearActuator(int stepPin, int dirPin, int address) : driver(&TMC_SERIAL_PORT, TMC_R_SENSE, address), motor(AccelStepper::DRIVER, stepPin, dirPin) {};
    ~LinearActuator() {};
    void setup();
    bool calibrateRight();
    bool calibrateLeft();
    bool checkRightCalibration();
    // bool checkLeftCalibration();
    void setSpeed(float speed) { motor.setSpeed(min(speed, LINEAR_ACTUATOR_MAX_SPEED) * MICRO_STEPS_PER_MM); }
    void setMaxSpeed(float speed) { motor.setMaxSpeed(min(speed, LINEAR_ACTUATOR_MAX_SPEED) * MICRO_STEPS_PER_MM); }
    void setAcceleration(float acceleration) { motor.setAcceleration(min(acceleration, LINEAR_ACTUATOR_MAX_ACCELERATION) * MICRO_STEPS_PER_MM); }
    void moveTo(float position) { motor.moveTo(saturate(position, leftLimit, rightLimit) * MICRO_STEPS_PER_MM); }
    void moveRight() { moveTo(rightLimit); }
    void moveLeft() { moveTo(leftLimit); }
    void stop() { motor.stop(); }
    void instantStop();
    int run();
    float currentPosition() { return motor.currentPosition() / MICRO_STEPS_PER_MM; }
    float amplitude() { return rightLimit - leftLimit; }
    bool isRightCalibrated() { return rightLimit < INT_MAX; }
    bool isLeftCalibrated() { return leftLimit > INT_MIN; }
    bool isCalibrated() { return isRightCalibrated() && isLeftCalibrated(); }

#ifndef EVERYTHING_PUBLIC
private:
#endif
    float rightLimit = INT_MAX;
    float leftLimit = INT_MIN;
    TMC2209Stepper driver;
    AccelStepper motor;
    void setCurrentPosition(float position) { motor.setCurrentPosition(position * MICRO_STEPS_PER_MM); }
    RunStatus::Status status = RunStatus::IDLE;
};

#endif