#include "config.hpp" 
#include <Arduino.h>
#pragma once

struct Inputs
{
    int volume = 0;
    int level = 0;
    int light = 0;
    bool mode_pb = false;
    bool mode_a = false, mode_b = false;
    int mode = 0;
    bool reset = false;
    unsigned long last_debounce_time_A = 0;
    unsigned long last_debounce_time_B = 0;
    bool stableModeA = false; // État stable de mode_a
    bool stableModeB = false; // État stable de mode_b

    // Méthode pour mettre à jour les valeurs d'inputs
    void refresh(const Inputs &inputs)
    {
        mode_pb = inputs.mode_pb;
        mode_a = inputs.mode_a;
        mode_b = inputs.mode_b;
        mode = inputs.mode;
        reset = inputs.reset;
    }
};

struct Outputs
{
    bool status_led = false;
};

class Corner
{
public:
    Corner() {};

    void setup_corner()
    {
        pinMode(VOLUME_PIN, INPUT);
        pinMode(LEVEL_PIN, INPUT);
        pinMode(LIGHT_PIN, INPUT);
        pinMode(MODE_PB_PIN, INPUT_PULLUP);
        pinMode(MODE_PIN_A, INPUT_PULLUP);
        pinMode(MODE_PIN_B, INPUT_PULLUP);
        pinMode(RESET_PIN, INPUT_PULLUP);
        pinMode(STATUS_LED, OUTPUT);
    }

    void loop_corner()
    {
        readInputs();
        sendInputs();
    }

private:
    Inputs inputs, lastInputs;
    Outputs outputs;

    void readInputs()
    {
        inputs.volume = analogRead(VOLUME_PIN);
        inputs.level = analogRead(LEVEL_PIN);
        inputs.light = analogRead(LIGHT_PIN);
        inputs.mode_pb = !digitalRead(MODE_PB_PIN);
        inputs.mode_a = !digitalRead(MODE_PIN_A);
        inputs.mode_b = !digitalRead(MODE_PIN_B);
        inputs.reset = !digitalRead(RESET_PIN);
    }

    void sendInputs()
    {
        // Vérification des changements significatifs
        if (abs(inputs.volume - lastInputs.volume) > ANTI_NOISE_THRESHOLD)
        {
            send(VOLUME_KEY, VALUE_ACTION_KEY, inputs.volume);
            lastInputs.volume = inputs.volume;
        }

        if (abs(inputs.level - lastInputs.level) > ANTI_NOISE_THRESHOLD)
        {
            send(LEVEL_KEY, VALUE_ACTION_KEY, inputs.level);
            lastInputs.level = inputs.level;
        }

        if (abs(inputs.light - lastInputs.light) > ANTI_NOISE_THRESHOLD)
        {
            send(LIGHT_KEY, VALUE_ACTION_KEY, inputs.light);
            lastInputs.light = inputs.light;
        }

        // Gestion des boutons mode
        if (inputs.mode_a != lastInputs.mode_a)
        {
            if (inputs.mode_b) 
            {
                inputs.mode++;
                if (inputs.mode > NB_MODES){
                    inputs.mode = NB_MODES;
                }
                send(MODE_KEY, INCREMENT_ACTION_KEY, inputs.mode);
            }
            else
            {
                inputs.mode--;
                // Limitation des modes à une plage de 0 à NB_MODES
                if (inputs.mode < 0){
                    inputs.mode = 0;
                }
                send(MODE_KEY, DECREMENT_ACTION_KEY, inputs.mode);

            }
        }
        lastInputs.mode_a = inputs.mode_a;
        lastInputs.mode_b = inputs.mode_b;

        

        // Gestion du bouton mode_pb
        if (inputs.mode_pb != lastInputs.mode_pb)
        {
            if (inputs.mode_pb)
            {
                send(MODE_PB_KEY, PUSH_ACTION_KEY, inputs.mode);
            }
            else
            {
                send(MODE_PB_KEY, RELEASE_ACTION_KEY);
            }
            lastInputs.mode_pb = inputs.mode_pb;
        }

        // Gestion du bouton reset
        if (inputs.reset != lastInputs.reset)
        {
            if (inputs.reset)
                send(RESET, PUSH_ACTION_KEY);
            else
                send(RESET, RELEASE_ACTION_KEY);
            lastInputs.reset = inputs.reset;
        }

        // Met à jour l'état précédent des inputs
        lastInputs.refresh(inputs);
    }

    // Méthode générique d'envoi de données
    template <typename T>
    void send(const String &key, const String &action, T value)
    {
        Serial.print(key);
        Serial.print("/");
        Serial.print(action);
        Serial.print("/");
        Serial.println(value);
    }

    // Surcharge pour envoyer sans valeur
    void send(const String &key, const String &action)
    {
        Serial.print(key);
        Serial.print("/");
        Serial.println(action);
    }
};
