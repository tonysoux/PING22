#define EVERYTHING_PUBLIC
#include "PING.hpp"

void setup() 
{
    Serial.begin(115200);
    PING::setup();
    Serial.println("Setup done");
    PING::player1.actuator.moveRight();   

}
unsigned long lastTime = 0;

void loop()
{
    PING::player1.actuator.run();
    if (millis() - lastTime > 1000)
    {
        lastTime = millis();
        Serial.println(PING::player1.actuator.currentPosition());
    }
}

// #include <Arduino.h>
// #include <AccelStepper.h>
// #include <TMCStepper.h>
// #include "config.h"

// #define MICRO_STEPS_PER_MM (float)STEPS_PER_REVOLUTION / PULLEY_TEETH / BELT_PITCH * (1 << MICROSTEP_POWER_OF_2)
// AccelStepper motor = AccelStepper(AccelStepper::DRIVER, P1_STEP_PIN, P1_DIR_PIN);
// TMC2209Stepper driver = TMC2209Stepper(&TMC_SERIAL_PORT, TMC_R_SENSE, TMC1_ADDRESS);
// void setup()
// {
//     Serial.begin(115200);
//     driver.begin();                                    // begin driver
//     driver.toff(4);                                    // set driver toff
//     driver.blank_time(24);                             // set driver blank time (time between two chopper off times)
//     driver.rms_current(RMS_CURRENT);                   // set driver RMS current
//     driver.microsteps(1 << MICROSTEP_POWER_OF_2);      // set driver microsteps

//     motor.setMaxSpeed(100 * MICRO_STEPS_PER_MM);
//     motor.setAcceleration(1 * MICRO_STEPS_PER_MM);
//     motor.enableOutputs();
//     motor.moveTo(100 * MICRO_STEPS_PER_MM);
//     Serial.println("MICRO_STEPS_PER_MM");
//     Serial.println(MICRO_STEPS_PER_MM);

// }

// unsigned long lastTime = 0;
// void loop()
// {
//     motor.run();
//     if (motor.distanceToGo() == 0)
//     {
//         motor.moveTo(-motor.currentPosition());
//     }

//     if (millis() - lastTime > 1000)
//     {
//         lastTime = millis();
//         Serial.print("Current position: ");
//         Serial.print(motor.currentPosition() / MICRO_STEPS_PER_MM);
//         Serial.print(" mm, \t");
//         Serial.print("stallguard: ");
//         Serial.println(driver.SG_RESULT());
//     }
// }

