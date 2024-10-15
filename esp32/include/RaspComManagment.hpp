/* 
    RaspComManagment is a class that will be used to manage the communication with the Raspberry Pi.
*/

#ifndef RASPCOMMANAGMENT_HPP
#define RASPCOMMANAGMENT_HPP

class RaspComManagment
{
  
public:
    RaspComManagment(int txPin, int rxPin, int baudRate);
    ~RaspComManagment();

    void setup();
};
#endif