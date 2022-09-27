#include <Pattern.h>

// Initialise Sensor

class BoxSide::BoxSide {

    bool isActive;

    // Initialise Timers
    long servoTimerEndTime;
    long servoTimerLength = 1000;
    bool servoTimerStarted;
    
    int *lights; //Save space and use pointer to array
    Servo servo;
    int sensorPin;

    Pattern activePattern;

    public:
        BoxSide(Servo sv, int *l, int sen) {
            servo = sv;
            *lights = *l;
            sensorPin = sen;
        }

    // Call process every frame
    void process() {
        if (!isActive) {
            if(analogRead(sensor) < SENSITIVITY) {
                onSensorTriggered();
            }
            return;
        }

        // Timeout after one second
        if(servoTimerStarted) {
            if(millis() >= servoTimerEndTime) {
                timerTimeOut();
            }
        }
    }

    // Method to define what happens when sensor is triggered
    void onSensorTriggered() {
        if(isActive) {
            return;
        }
        isActive = true;
        startTimer();
    }

    // Method to define what happens when the timer starts
    void startTimer() {
        servoTimerEndTime = millis() + servoTimerLength;
        servoTimerStarted = true;
    }
    
    // Method to define what happens when the timer timeouts
    void timerTimeOut() {
        servoTimerStarted = false;
        servo.write(90);    
    }
}