#include <Servo.h>
//#include <Adafruit_NeoPixel.h>
const int SENSITIVITY = 950;

//Servo
const int DEFAULT_SERVO_POS = 0;
const int SERVO_END_POS = 90;

const int NEO_PIXEL_COUNT = 24;

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
    long servoReturnTimerLength = 500;
    bool servoTimerStarted;
    
    int *lights; //Save space and use pointer to array
    //Adafruit_NeoPixel light;
    
    Servo servo;
    byte sensorPin;

    Pattern activePattern();
    public:
      BoxSide(Servo sv, int *l, byte sen) {
        servo = sv;
        *lights = *l;
        sensorPin = sen;
        //light = Adafr
       }
      // Call process every frame
      void process() {
        if (!isActive) {
          if(analogRead(sensorPin) < SENSITIVITY) {
            onSensorTriggered();
          }
          return;
        }
        else {
          if(millis() > servoTimerEndTime) {
            timerTimeOut();
          }
        }
    }

    // Method to define what happens when sensor is triggered
    void onSensorTriggered() {
        isActive = true;
        startTimer();
    }

    // Method to define what happens when the timer starts
    void startTimer() {
        setTimer(servoTimerLength);
    }
    
    // Method to define what happens when the timer timeouts
    void timerTimeOut() {
        //WRITE SERVO TO PUSH BALL OUT
        if(servo.read() == DEFAULT_SERVO_POS) {
          servo.write(SERVO_END_POS);
          //Start timer to return servo to default
          setTimer(servoReturnTimerLength);
        }
        //WRITE SERVO TO DEFAULT POSITION; SERVO READY TO BE TRIGGERED
        else {
          servo.write(DEFAULT_SERVO_POS);
          isActive = false;         
        }
    }

    void setTimer(int timerLength) {
      servoTimerEndTime = millis()+timerLength;
    }
};


const byte sensorPinLeft = A0;
const byte sensorPinRight = A1;

int lightPinsUp[1] = {1};
int lightPinsDown[1] = {2};

int servoPinLeft = 10;
int servoPinRight = -1;

Servo leftServo;
Servo rightServo;

// Define left and right box-side variables
int *p = lightPinsUp;
BoxSide leftSide(leftServo, p, sensorPinLeft);
int *p2 = lightPinsDown;
BoxSide rightSide(rightServo, p2, sensorPinRight);


void setup(){
  Serial.begin(4800);
  // Set pins to output
  for(int i = 0; i < sizeof(lightPinsUp); i++){
    //Symmetrical so pin count SHOULD be the same
    pinMode(lightPinsUp[i], OUTPUT);
    pinMode(lightPinsDown[i], OUTPUT);
  }


  leftServo.write(DEFAULT_SERVO_POS);
  rightServo.write(DEFAULT_SERVO_POS);
  leftServo.attach(servoPinLeft);
  rightServo.attach(servoPinRight);


  pinMode(sensorPinLeft, INPUT);
  pinMode(sensorPinRight, INPUT);

}

void loop() {
  Serial.println(analogRead(sensorPinLeft));
  leftSide.process();
  rightSide.process();
}
