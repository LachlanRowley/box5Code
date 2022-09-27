#include <Servo.h>
//#include <Adafruit_NeoPixel.h>
const int SENSITIVITY = 250;

class Pattern {
    public:
        virtual void doPattern() {}

  void setup()
  {
    // Initialise Pins
    pinMode(1, OUTPUT);
    pinMode(4, OUTPUT);
  }

  //does the pattern
  void loop()
  { 
    for (int i = 0; i < 12; i++){
      digitalWrite(i, LOW);
      digitalWrite((i+1), HIGH);
      digitalWrite((i+2), HIGH);
      delay(100);
    }
  }
};

class BoxSide {
    bool isActive;

    // Initialise Timers
    long servoTimerEndTime;
    long servoTimerLength = 1000;
    bool servoTimerStarted;
    
    int *lights; //Save space and use pointer to array
    Servo servo;
    byte sensorPin;

    Pattern activePattern;
    public:
      BoxSide(Servo sv, int *l, byte sen) {
        servo = sv;
        *lights = *l;
        sensorPin = sen;
      }
      // Call process every frame
      void process() {
        if (!isActive) {
          if(analogRead(sensorPin) < SENSITIVITY) {
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
};


const byte sensorPinLeft = A0;
const byte sensorPinRight = A1;

int lightPinsUp[1] = {1};
int lightPinsDown[1] = {2};

int servoPinLeft = -1;
int servoPinRight = -1;

Servo leftServo;
Servo rightServo;

// Define left and right box-side variables
int *p = lightPinsUp;
BoxSide leftSide(leftServo, p, sensorPinLeft);
int *p2 = lightPinsDown;
BoxSide rightSide(rightServo, p2, sensorPinRight);


void setup(){
  Serial.begin(9600);
  // Set pins to output
  for(int i = 0; i < sizeof(lightPinsUp); i++){
    //Symmetrical so pin count SHOULD be the same
    pinMode(lightPinsUp[i], OUTPUT);
    pinMode(lightPinsDown[i], OUTPUT);
  }

  leftServo.attach(servoPinLeft);
  rightServo.attach(servoPinRight);


  pinMode(sensorPinLeft, INPUT);
  pinMode(sensorPinRight, INPUT);

}

void loop() {

  leftSide.process();
  rightSide.process();
}
