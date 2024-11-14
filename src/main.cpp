// #define EVERYTHING_PUBLIC
// #include "PING.hpp"

// void setup()
// {
//     Serial.begin(115200);
//     PING::setup();
//     Serial.println("Setup done");
//     PING::player1.actuator.moveRight();

// }
// unsigned long lastTime = 0;

// void loop()
// {
//     PING::player1.actuator.run();
//     if (millis() - lastTime > 1000)
//     {
//         lastTime = millis();
//         Serial.println(PING::player1.actuator.currentPosition());
//     }
//     vTaskDelay(1);
// }

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

#include <HardwareSerial.h>
#include <TMCStepper.h>

// #define DIAG_PIN_2         19          // STALL motor 2
// #define EN_PIN_2           5          // Enable
#define DIR_PIN_2 33          // Direction
#define STEP_PIN_2 32         // Step
#define SERIAL_PORT_2 Serial2 // TMC2208/TMC2224 HardwareSerial port
#define DRIVER_ADDRESS_2 0b00 // TMC2209 Driver address according to MS1 and MS2
#define R_SENSE_2 0.62f       // E_SENSE for current calc.
#define STALL_VALUE_2 200       // [0..255]

hw_timer_t *timer1 = NULL;
TMC2209Stepper driver2(&SERIAL_PORT_2, R_SENSE_2, DRIVER_ADDRESS_2);

void IRAM_ATTR onTimer()
{

    digitalWrite(STEP_PIN_2, !digitalRead(STEP_PIN_2));
}

void activate_interrupt()
{
    {
        cli();                                        // stop interrupts
        timer1 = timerBegin(3, 4, true);              // Initialize timer 4. Se configura el timer,  ESP(0,1,2,3)
                                                      // prescaler of 8, y true es una bandera que indica si la interrupcion se realiza en borde o en nivel
        timerAttachInterrupt(timer1, &onTimer, true); // link interrupt with function onTimer
        timerAlarmWrite(timer1, 8000, true);           // En esta funcion se define el valor del contador en el cual se genera la interrupción del timer
        timerAlarmEnable(timer1);                     // Enable timer
        sei();                                        // allow interrupts
    }
}

void setup()
{
    Serial.begin(115200); // Init serial port and set baudrate
    while (!Serial)
        ; // Wait for serial port to connect
    Serial.println("\nStart...");
    SERIAL_PORT_2.begin(115200);
    delay(1000);

    //   pinMode(DIAG_PIN_2 ,INPUT);
    //   pinMode(EN_PIN_2 ,OUTPUT);
    pinMode(STEP_PIN_2, OUTPUT);
    pinMode(DIR_PIN_2, OUTPUT);

    //   digitalWrite(EN_PIN_2 ,LOW);
    digitalWrite(DIR_PIN_2, LOW);


       driver2.begin();
       driver2.toff(4);
       driver2.blank_time(24);
       driver2.rms_current(100); // mA
       driver2.microsteps(16);
       driver2.TCOOLTHRS(0xFFFFF); // 20bit max
       driver2.semin(5);
       driver2.semax(2);
       driver2.sedn(0b01);
       driver2.SGTHRS(STALL_VALUE_2);
       activate_interrupt();
}
bool flag = false;
void loop()
{
    static uint32_t last_time = 0;
    uint32_t ms = millis();
    if ((ms - last_time) > 100)
    { // run every 0.1s
        last_time = ms;

        Serial.print("0 ");
        Serial.print(driver2.SG_RESULT(), DEC);
        Serial.print(" ");
        Serial.println(driver2.cs2rms(driver2.cs_actual()), DEC);
    }
    if (ms > 10000 && !flag)
    {
        flag = true;
        driver2.shaft(true);
        driver2.SGTHRS(0);
    }
}
