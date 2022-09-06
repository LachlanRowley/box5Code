#include <Pattern.h>

// Initialise Sensor

class BoxSide::BoxSide {

    bool isActive

    // Initialise Timers
    long timerEndTime;
    long timerLength = 1000;
    bool timerStarted;
    
    public:

    // Call process every frame
    void process() {
        if (!isActive) {
            return;
        }

        // Timeout after one second
        if(timerStarted) {
            if(millis() >= timerEndTime) {
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
        timerEndTime = millis() + timerLength;
    }
    
    // Method to define what happens when the timer timeouts
    void timerTimeOut() {
        timerStarted = false;
        //Motor on
    }
}