#include "LinearActuator.hpp"
// #include <SoftwareSerial.h>

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

int LinearActuator::run()
{
    motor.run();

    // check for collision using driver's stallguard
    if (driver.SG_RESULT() > STALL_VALUE)
    {
        motor.setSpeed(0);
        motor.runSpeed();
        return RunStatus::COLLISION;
    }
    return RunStatus::RUNNING;
}