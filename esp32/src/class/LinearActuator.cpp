#include "LinearActuator.hpp"

LinearActuator::LinearActuator(int stepPin, int dirPin, int address) : driver(&TMC_SERIAL_PORT, TMC_R_SENSE, address), motor(AccelStepper::DRIVER, stepPin, dirPin)
{
}

LinearActuator::~LinearActuator()
{
}