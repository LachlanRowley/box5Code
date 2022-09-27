#include <Servo.h>
#include <Adafruit_NeoPixel.h>
const int SENSITIVITY = 250;

class Pattern {
	int *lights;
	int activeLight = 0;
	long timeLastUpdate = 0;
	int timeDelay = 1000;
  
    void patternStart() {
      digitalWrite(lights[0], HIGH);
      timeLastUpdate = millis();
    }
    void patternInc() {
      if(millis() >= timeLastUpdate + timeDelay) {
        digitalWrite(lights[activeLight], LOW);
        activeLight = (activeLight+1) % sizeof(lights);
        digitalWrite(lights[activeLight], HIGH);
        timeLastUpdate = millis();
        }
    }  
         void setup()
  {
    // Initialise Pins
    pinMode(1, OUTPUT);
    pinMode(4, OUTPUT);
  }
};

class BoxSide {
    bool isActive = false;

    // Initialise Timers
    long servoTimerEndTime;
    long servoTimerLength = 1000;
    bool servoTimerStarted;
    
    int *lights; //Save space and use pointer to array
    Servo servo;
    byte sensorPin;

    Pattern activePattern();
    public:
      BoxSide(Servo sv, int *l, byte sen) {
        servo = sv;
        *lights = *l;
        sensorPin = sen;
       }
      // Call process every frame
      void process() {
        if (!isActive) {
          Serial.println(analogRead(sensorPin));
          if(analogRead(sensorPin) < SENSITIVITY) {
            onSensorTriggered();
          }
          return;
        }
        else {
          if(millis() > servoTimerEndTime) {
            isActive = false;
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
        servo.write(2);    
    }
};


const byte sensorPinLeft = A0;
const byte sensorPinRight = A1;

int lightPinsUp[1] = {1};
int lightPinsDown[1] = {2};

int servoPinLeft = 12;
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

