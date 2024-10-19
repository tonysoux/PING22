#ifndef BEAMSWITCH_HPP
#define BEAMSWITCH_HPP

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "config.h"

class BeamSwitch
{
private:
    static IRsend emitter;      // Initialize the IR LED sender
    static void emit_task(void *pvParameters);
    static TaskHandle_t emit_task_handle;
    static int64_t lastEmitTime;
    static uint16_t rawSignal[];  // Un signal infrarouge basique de 500 µs on, 500 µs off
    IRrecv irrecv;       // Initialize the IR receiver
    decode_results results;        // Struct for decoded IR data
    int lastReceiveTime = 0;
    bool state = false;
    TaskHandle_t receive_task_handle;

public:
    static bool emit;
    BeamSwitch(int beamSwitchRPin) : irrecv(beamSwitchRPin) {};
    ~BeamSwitch(){};
    static void setup_common_emitter();
    void setup();
    void check();
    bool getState(){return state;};
    
};

#endif