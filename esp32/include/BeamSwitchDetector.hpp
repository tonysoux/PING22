#ifndef BEAMSWITCHDETECTOR_HPP
#define BEAMSWITCHDETECTOR_HPP
#include <IRrecv.h>
class BeamSwitchDetector
{
private:
    /* data */
public:
    BeamSwitchDetector(int beamSwitchTPin, int beamSwitchRPin);
    ~BeamSwitchDetector();
    int loop();
};

BeamSwitchDetector::BeamSwitchDetector(int beamSwitchTPin, int beamSwitchRPin)
{
}

BeamSwitchDetector::~BeamSwitchDetector()
{
}

int BeamSwitchDetector::loop()
{

    return 0;
}

#endif