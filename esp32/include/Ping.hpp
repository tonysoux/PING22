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
private:   
    PING(){};
    static Player player1, player2, player3, player4;
    static RaspComManagment raspComManager;
public:
    ~PING(){};
    static void setup();
    static void loop();
};

Player PING::player1 = Player(P1_STEP_PIN, P1_DIR_PIN, P1_RX_PIN, P1_SOLENOID_PIN, P1_BEAM_T_PIN, P1_BEAM_R_PIN);
Player PING::player2 = Player(P2_STEP_PIN, P2_DIR_PIN, P2_RX_PIN, P2_SOLENOID_PIN, P2_BEAM_T_PIN, P2_BEAM_R_PIN);
Player PING::player3 = Player(P3_STEP_PIN, P3_DIR_PIN, P3_RX_PIN, P3_SOLENOID_PIN, P3_BEAM_T_PIN, P3_BEAM_R_PIN);
Player PING::player4 = Player(P4_STEP_PIN, P4_DIR_PIN, P4_RX_PIN, P4_SOLENOID_PIN, P4_BEAM_T_PIN, P4_BEAM_R_PIN);
RaspComManagment PING::raspComManager = RaspComManagment(RASP_TX_PIN, RASP_RX_PIN, RASP_BAUD_RATE);

void PING::setup()
{
    raspComManager.setup();
}

void PING::loop()
{
    player1.loop();
    player2.loop();
    player3.loop();
    player4.loop();
    // raspComManager.loop();
}
#endif