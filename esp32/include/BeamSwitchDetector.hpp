#ifndef BEAMSWITCHDETECTOR_HPP
#define BEAMSWITCHDETECTOR_HPP

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>
#include "config.h"

class BeamSwitchDetector
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
    BeamSwitchDetector(int beamSwitchRPin) : irrecv(beamSwitchRPin) {};
    ~BeamSwitchDetector(){};
    static void setup_common_emitter();
    void setup();
    void check();
    bool getState(){return state;};
    
};

#endif