#include "LinearActuator.hpp"

void LinearActuator::setup()
{
    driver.begin();                                    // begin driver
    driver.toff(4);                                    // set driver toff
    driver.blank_time(24);                             // set driver blank time (time between two chopper off times)
    driver.rms_current(RMS_CURRENT);                   // set driver RMS current
    driver.microsteps(1 << MICROSTEP_POWER_OF_2);      // set driver microsteps
    setMaxSpeed(LINEAR_ACTUATOR_MAX_SPEED);            // set max speed
    setAcceleration(LINEAR_ACTUATOR_MAX_ACCELERATION); // set acceleration
    motor.enableOutputs();                             // enable motor outputs
}

bool LinearActuator::calibrateRight()
{
    setMaxSpeed(CALIBRATION_COARSE_SPEED);
    moveRight();
    if (status != RunStatus::COLLISION)
        return false;
    rightLimit = currentPosition();
    if (leftLimit > INT_MIN)
        motor.setCurrentPosition(amplitude() * MICRO_STEPS_PER_MM / 2);
    setMaxSpeed(LINEAR_ACTUATOR_MAX_SPEED);
    return true;
}

bool LinearActuator::calibrateLeft()
{
    setMaxSpeed(CALIBRATION_COARSE_SPEED);
    moveLeft();
    if (status != RunStatus::COLLISION)
        return false;
    leftLimit = currentPosition();
    if (rightLimit < INT_MAX)
        motor.setCurrentPosition( - amplitude() * MICRO_STEPS_PER_MM / 2);
    setMaxSpeed(LINEAR_ACTUATOR_MAX_SPEED);
    return true;
}

void LinearActuator::instantStop()
{
    motor.setSpeed(0);
    motor.runSpeed();
}

int LinearActuator::run()
{
    motor.run();
    if (driver.SG_RESULT() > STALL_VALUE)
    {
        instantStop();
        return RunStatus::COLLISION;
    }
    return RunStatus::RUNNING;
}

