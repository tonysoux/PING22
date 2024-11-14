// #include <unity.h>
#define EVERYTHING_PUBLIC
#include "PING.hpp"


/*
    mesure du temps d'activation : on allume l'émetteur et on mesure le temps que met le récepteur à détecter le signal
    mesure du temps de désactivation : on éteint l'émetteur et on mesure le temps que met le récepteur à ne plus détecter le signal

    protocole de test :
    - initialisation de l'émetteur avec 'emit' à false et on lance la tâche d'émission avec 'setup_common_emitter'
    - initialisation du récepteur avec 'setup' et on lance la tâche de réception
    - on allume l'émetteur en mettant 'emit' à true et en déclenchant le chrono
    - on arrête le chrono quand le récepteur détecte le signal, avec un timeout de 500ms
    - on envoie sur le moniteur série le temps mesuré
    - on éteint l'émetteur en mettant 'emit' à false et en déclenchant le chrono
    - on arrête le chrono quand le récepteur ne détecte plus le signal, avec un timeout de 500ms
*/



void setup() 
{
    Serial.begin(115200);
    Serial.println("BeamSwitch test");
    BeamSwitch::emit = false;
    BeamSwitch::setup_common_emitter();
    PING::player1.beamSwitch.setup();
    PING::player2.beamSwitch.setup();
    PING::player3.beamSwitch.setup();
    PING::player4.beamSwitch.setup();

    xTaskCreatePinnedToCore(
        PING::BeamSwitchReceive_task,         /* Function to implement the task */
        "BeamSwitchReceive_task",             /* Name of the task */
        10000,                                /* Stack size in words */
        NULL,                                 /* Task input parameter */
        TASK_BEAM_RECEIVER_PRIORITY,          /* Priority of the task */
        &PING::BeamSwitchReceive_task_handle, /* Task handle. */
        TASK_BEAM_RECEIVER_CORE               /* Core where the task should run */
    );
    delay(100);
    BeamSwitch::emit = true;
    unsigned long start = esp_timer_get_time();
    unsigned long dt[4] = {0, 0, 0, 0};
    unsigned long t = 0;
    do
    {
        t = esp_timer_get_time();
        if (PING::player1.beamSwitch.getState())
            dt[0] = t-start;
        if (PING::player2.beamSwitch.getState())
            dt[1] = t-start;
        if (PING::player3.beamSwitch.getState())
            dt[2] = t-start;
        if (PING::player4.beamSwitch.getState())
            dt[3] = t-start;
        
        if (dt[0] && dt[1] && dt[2] && dt[3])
            break;

    } while (t-start < 500000); // 500ms of timeout

    
    Serial.print("Activation times :");
    Serial.print(dt[0]);
    Serial.print(" ");
    Serial.print(dt[1]);
    Serial.print(" ");
    Serial.print(dt[2]);
    Serial.print(" ");
    Serial.println(dt[3]);

    dt[0] = 0;
    dt[1] = 0;
    dt[2] = 0;
    dt[3] = 0;

    start = esp_timer_get_time();
    BeamSwitch::emit = false;
    do
    {
        t = esp_timer_get_time();
        if (!PING::player1.beamSwitch.getState())
            dt[0] = t-start;
        if (!PING::player2.beamSwitch.getState())
            dt[1] = t-start;
        if (!PING::player3.beamSwitch.getState())
            dt[2] = t-start;
        if (!PING::player4.beamSwitch.getState())
            dt[3] = t-start;
        
        if (dt[0] && dt[1] && dt[2] && dt[3])
            break;

    } while (t-start < 500000); // 500ms of timeout

    Serial.print("Deactivation times :");
    Serial.print(dt[0]);
    Serial.print(" ");
    Serial.print(dt[1]);
    Serial.print(" ");
    Serial.print(dt[2]);
    Serial.print(" ");
    Serial.println(dt[3]);
}

void loop()
{
    Serial.println(PING::player1.beamSwitch.getState());
    delay(100);
}