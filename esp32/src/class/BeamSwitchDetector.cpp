#include "BeamSwitchDetector.hpp"

IRsend BeamSwitchDetector::emitter = IRsend(P123_BEAM_T_PIN);
bool BeamSwitchDetector::emit = true;
int64_t BeamSwitchDetector::lastEmitTime = 0;
TaskHandle_t BeamSwitchDetector::emit_task_handle;
uint16_t BeamSwitchDetector::rawSignal[] = {500, 500};  // Un signal infrarouge basique de 500 µs on, 500 µs off


void BeamSwitchDetector::emit_task(void *pvParameters)
{
    for (;;)
        if (emit)
        {
            emitter.sendRaw(rawSignal, 2, 38);  // 38kHz fréquence
            lastEmitTime = esp_timer_get_time();
        }
        vTaskDelay(BEAM_SWITCH_DELAY_us / portTICK_PERIOD_MS);  // Short delay for timing

}

void BeamSwitchDetector::setup_common_emitter()
{
    emitter.begin();           // Start the IR LED
    xTaskCreatePinnedToCore (
    BeamSwitchDetector::emit_task,   /* Function to implement the task */
    "emit_task",                     /* Name of the task */
    1000,                           /* Stack size in words */
    NULL,                            /* Task input parameter */
    1,                               /* Priority of the task */
    &BeamSwitchDetector::emit_task_handle,  /* Task handle. */
    1                                /* Core where the task should run */
);
}


void BeamSwitchDetector::setup()
{
    irrecv.enableIRIn();
}

void BeamSwitchDetector::check()
{
    uint64_t currentTime = esp_timer_get_time();
    if (irrecv.decode(&results))
        {
            irrecv.resume();
            lastReceiveTime = currentTime;
        }
    
    int dt = lastEmitTime - lastReceiveTime;
    if (dt > BEAM_SWITCH_TIMEOUT_us)
        state = true;
    else
        state = false;
}

