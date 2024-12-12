#include "config.hpp"

struct Inputs
{
    int volume;
    int level;
    int light;
    bool mode_pb;
    bool mode_a, mode_b;
    int mode;
    bool reset;

    void refresh(Inputs inputs)
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
    bool status_led;
};

class Corner
{
public:
    Corner(){};

    void setup()
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
    void loop()
    {
        readInputs();
        sendInputs();
        // process inputs
        // update outputs
        // write outputs
        // writeOutputs();
    }

private:
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

        if (inputs.mode_pb != lastInputs.mode_pb)
        {
            if (inputs.mode_pb)
                send(MODE_PB_KEY, PUSH_ACTION_KEY);
            else
                send(MODE_PB_KEY, RELEASE_ACTION_KEY);
        }
        
        if (inputs.mode_a != lastInputs.mode_a)
        {
            if (!inputs.mode_a)
                if (!inputs.mode_b)
                    send(MODE_KEY, INCREMENT_ACTION_KEY);
        }
        
        if (inputs.mode_b != lastInputs.mode_b)
        {
            if (!inputs.mode_b)
                    if (!inputs.mode_a)

                        send(MODE_KEY, DECREMENT_ACTION_KEY);
        }
        
        if (inputs.reset != lastInputs.reset)
        {
            if (inputs.reset)
                send(RESET, PUSH_ACTION_KEY);
            else
                send(RESET, RELEASE_ACTION_KEY);
        }
        lastInputs.refresh(inputs);
    }

    template <typename T>
    void send(String key, String action, T value)
    {
        Serial.print(key);
        Serial.print("/");
        Serial.print(action);
        Serial.print("/");
        Serial.println(value);
    }
    void send(String key, String action)
    {
        Serial.print(key);
        Serial.print("/");
        Serial.println(action);
    }
    Inputs inputs, lastInputs;
    Outputs outputs;
};