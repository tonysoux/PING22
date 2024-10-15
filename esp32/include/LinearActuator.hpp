#ifndef LINEARACTUATOR_HPP
#define LINEARACTUATOR_HPP

class LinearActuator
{
private:
    /* data */
public:
    LinearActuator(int stepPin, int dirPin, int rxPin);
    ~LinearActuator();
};

#endif