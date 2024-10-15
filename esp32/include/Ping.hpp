/*
PING is the main class of the project. It is responsible for the initialization of the game and the management of the game loop.
Everything may be static, as there is only one instance of the game.
*/

#ifndef PING_HPP
#define PING_HPP

#include "Player.hpp"
#include "config.h"
#include "RaspComManagment.hpp"

class PING
{
// private:  
public: 
    PING(){};
    static Player player1, player2, player3, player4;
    static RaspComManagment raspComManager;
    static TaskHandle_t BeamSwitch_task_handle;
    static void BeamSwitch_task(void *pvParameters);

public:
    ~PING(){};
    static void setup();

};

#endif