#include <Arduino.h>

class Pump
{
private:
    unsigned long startMillis;
    float _ratio;
    int timePeriodMillis = 1000;
    int _pin;
    int _speedPWM;
    float _compensationRatio = 1;

    bool shouldPump()
    {
        unsigned long timeSinceStart = millis() - startMillis;
        int timeElapsedInPeriod = timeSinceStart % timePeriodMillis;
        float percentElapsedOfPeriod = (float)timeElapsedInPeriod / (float)timePeriodMillis;
        
        return percentElapsedOfPeriod <= _ratio;
    }

public:
    Pump() {}
    Pump(int pin, float speedPWM, float compensationRatio)
    {
        _pin = pin;
        _speedPWM = speedPWM;
        _compensationRatio = compensationRatio;

        pinMode(pin, OUTPUT);
    }

    void start(float ratio)
    {
        startMillis = millis();
        _ratio = ratio;

        Serial.println("Start ratio: " + String(ratio, 2));
    }

    void pump()
    {
        if (shouldPump())
        {
            analogWrite(_pin, _speedPWM * _compensationRatio);
            // Serial.println("Should pump");
        }
        else
        {
            analogWrite(_pin, 0);
            // Serial.println("Shout NOT pump");
        }
    }

    void stop()
    {
        analogWrite(_pin, 0);
    }
};
