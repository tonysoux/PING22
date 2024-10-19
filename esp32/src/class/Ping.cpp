#include "Ping.hpp"

TaskHandle_t PING::BeamSwitchReceive_task_handle;
#if defined P1_STEP_PIN && defined P1_DIR_PIN && defined TMC_RX && defined P1_SOLENOID_PIN && defined P1_BEAM_R_PIN
#define P1
#endif
#if defined P2_STEP_PIN && defined P2_DIR_PIN && defined TMC_RX && defined P2_SOLENOID_PIN && defined P2_BEAM_R_PIN
#define P2
#endif
#if defined P3_STEP_PIN && defined P3_DIR_PIN && defined TMC_RX && defined P3_SOLENOID_PIN && defined P3_BEAM_R_PIN
#define P3
#endif
#if defined P4_STEP_PIN && defined P4_DIR_PIN && defined TMC_RX && defined P4_SOLENOID_PIN && defined P4_BEAM_R_PIN
#define P4
#endif

#ifdef P1
Player PING::player1 = Player(P1_STEP_PIN, P1_DIR_PIN, TMC1_ADDRESS, P1_SOLENOID_PIN, P1_BEAM_R_PIN);
#endif
#ifdef P2
Player PING::player2 = Player(P2_STEP_PIN, P2_DIR_PIN, TMC2_ADDRESS, P2_SOLENOID_PIN, P2_BEAM_R_PIN);
#endif
#ifdef P3
Player PING::player3 = Player(P3_STEP_PIN, P3_DIR_PIN, TMC3_ADDRESS, P3_SOLENOID_PIN, P3_BEAM_R_PIN);
#endif
#ifdef P4
Player PING::player4 = Player(P4_STEP_PIN, P4_DIR_PIN, TMC4_ADDRESS, P4_SOLENOID_PIN, P4_BEAM_R_PIN);
#endif

RaspComManagment PING::raspComManager = RaspComManagment(RASP_TX_PIN, RASP_RX_PIN, RASP_BAUD_RATE);

void PING::BeamSwitchReceive_task(void *pvParameters)
{
    for (;;)
    {
        #ifdef P1
        PING::player1.beamSwitch.check();
        #endif
        #ifdef P2
        PING::player2.beamSwitch.check();
        #endif
        #ifdef P3
        PING::player3.beamSwitch.check();
        #endif
        #ifdef P4
        PING::player4.beamSwitch.check();
        #endif
        vTaskDelay(TASK_BEAM_EMITTER_DELAY_MS / portTICK_PERIOD_MS);
    }
}
void PING::setup()
{
    BeamSwitch::setup_common_emitter();
    raspComManager.setup();
    #ifdef P1
    PING::player1.setup();
    #endif
    #ifdef P2
    PING::player2.setup();
    #endif
    #ifdef P3
    PING::player3.setup();
    #endif
    #ifdef P4
    PING::player4.setup();
    #endif
    
    xTaskCreatePinnedToCore(
        PING::BeamSwitchReceive_task, /* Function to implement the task */
        "BeamSwitchReceive_task",    /* Name of the task */
        10000,                 /* Stack size in words */
        NULL,                 /* Task input parameter */
        TASK_BEAM_RECEIVER_PRIORITY,                    /* Priority of the task */
        &PING::BeamSwitchReceive_task_handle, /* Task handle. */
        TASK_BEAM_RECEIVER_CORE                     /* Core where the task should run */
    );

}
