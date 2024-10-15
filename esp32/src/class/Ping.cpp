#include "Ping.hpp"

TaskHandle_t PING::BeamSwitch_task_handle;

Player PING::player1 = Player(P1_STEP_PIN, P1_DIR_PIN, P1_RX_PIN, P1_SOLENOID_PIN, P1_BEAM_R_PIN);

RaspComManagment PING::raspComManager = RaspComManagment(RASP_TX_PIN, RASP_RX_PIN, RASP_BAUD_RATE);

void PING::BeamSwitch_task(void *pvParameters)
{
    for (;;)
    {
        PING::player1.beamSwitch.check();
        vTaskDelay(BEAM_SWITCH_DELAY_us / 1000 / portTICK_PERIOD_MS);
    }
}
void PING::setup()
{
    BeamSwitchDetector::setup_common_emitter();
    raspComManager.setup();
    player1.setup();


    xTaskCreatePinnedToCore(
        PING::BeamSwitch_task, /* Function to implement the task */
        "BeamSwitchReceive_task",    /* Name of the task */
        10000,                 /* Stack size in words */
        NULL,                 /* Task input parameter */
        1,                    /* Priority of the task */
        &PING::BeamSwitch_task_handle, /* Task handle. */
        0                     /* Core where the task should run */
    );

}
