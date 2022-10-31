// Import Libraries
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// Initialise Servo Variables
const int DEFAULT_SERVO_POS = 100;
const int SERVO_END_POS = 250;
const int NEO_PIXEL_COUNT = 24;
const int SENSITIVITY = 1018;
const int PATTERNCOUNT = 6;

Adafruit_NeoPixel leftLight = Adafruit_NeoPixel(29,8);

class bouncingPattern {
  
  protected:
    Adafruit_NeoPixel light;
    int curOnLight = 0;
    long timeDelay = 50;
    long endTime;
    int width = 3;
    short dir = 1;  
  public:
    bouncingPattern() {}
    bouncingPattern(Adafruit_NeoPixel l) {
      light = l;
    }

        bool isActive = false;
        void process() {
            if(isActive) {
                if(millis() > endTime) {
                    patternInc();
                    endTime = millis()+timeDelay;
                }
            }
        }
    
  
  void patternStart() {
        light.clear();
    light.setPixelColor(curOnLight, light.Color(255, 255, 255));
    light.show();
    isActive = true;
        endTime = millis() + timeDelay;
  }
  
  void patternInc() {
    light.clear();
    curOnLight += dir;
    if(curOnLight + width  >= NEO_PIXEL_COUNT){
      dir = -1;
    }else if(curOnLight==0){
      dir = 1;
    }
    for(int i =0; i < width; i++){
      light.setPixelColor(curOnLight+i, light.Color(255,0,0));
    }
        light.show();
    }
    void patternEnd() {
    light.clear();
        curOnLight = 0;
    }
};

// Define Sequential Pattern Class
class SequentialPattern {
  protected:
    Adafruit_NeoPixel light;
    int curOnLight = 0;
    long timeDelay = 300;
    long endTime;
  public:
    SequentialPattern() {}
    SequentialPattern(Adafruit_NeoPixel l) {
      light = l;
    }

        bool isActive = false;
        void process() {
            if(isActive) {
                if(millis() > endTime) {
                    patternInc();
                    endTime = millis()+timeDelay;
                }
            }
        }
  
  void patternStart() {
        light.clear();
    light.setPixelColor(curOnLight, light.Color(random(0,255), random(0,255), random(0,255)));
    light.show();
    isActive = true;
        endTime = millis() + timeDelay;
  }
  
  void patternInc() {
    curOnLight++;
    curOnLight = curOnLight % NEO_PIXEL_COUNT;
    light.clear();    
    light.setPixelColor(curOnLight, light.Color(random(0,255), random(0,255), random(0,255)));
    light.show();
    }
    void patternEnd() {
    light.clear();
        curOnLight = 0;
    }
};

// Define ColumnsPattern Class
class ColumnsPattern {
  protected:
      Adafruit_NeoPixel light;
      int curOnLight = 0;
      long timeDelay = 100;
      long endTime;

  public:
      ColumnsPattern() {}
      ColumnsPattern(Adafruit_NeoPixel l) {
          light = l;
      }
      bool isActive = false;
      void process() {
          if (isActive){
              if (millis() > endTime){
                  patternInc();
                  endTime = millis() + timeDelay;
              }
          }
      }

      void patternStart() {
          light.clear();
          light.setPixelColor(curOnLight, (255, 0, 0));
          light.show();
          isActive = true;
          endTime = millis() + timeDelay;
      }

      void patternInc() {
          light.clear();

          if (curOnLight == 6) {
              curOnLight = 0;
          }
          curOnLight = curOnLight % NEO_PIXEL_COUNT;
          light.setPixelColor(curOnLight, light.Color(255, 0, 0));
          light.setPixelColor(curOnLight + 6 % 24, light.Color(255, 0, 0));
          light.setPixelColor(curOnLight + 12 % 24, light.Color(255, 0, 0));
          light.setPixelColor(curOnLight + 18 % 24, light.Color(255, 0, 0));
          light.show();
          curOnLight++;
      }
      void patternEnd() {
          light.clear();
          curOnLight = 0;
      }
};

// Define Row Pattern Class
class RowPattern {
  protected:
      Adafruit_NeoPixel light;
      int curOnLight = 0;
      long timeDelay = 100;
      long endTime;

  public:
      RowPattern() {}
      RowPattern(Adafruit_NeoPixel l) {
          light = l;
      }
      bool isActive = false;
      void process() {
          if (isActive) {
              if (millis() > endTime) {
                  patternInc();
                  endTime = millis() + timeDelay;
              }
          }
      }

  void patternStart() {
    Serial.println("Pat start");
    light.clear();
    light.setPixelColor(curOnLight, (255,0,0));
    light.show();
    isActive = true;
    endTime = millis() + timeDelay;
  }
  
  void patternInc() {
    light.clear(); 
    
    if (curOnLight == NEO_PIXEL_COUNT){
      curOnLight = 0;
    }
    
    curOnLight = curOnLight % NEO_PIXEL_COUNT;   
    light.setPixelColor(curOnLight, light.Color(255,0,0));
    light.setPixelColor(curOnLight + 1 % 24, light.Color(255,0,0));
    light.setPixelColor(curOnLight + 2 % 24, light.Color(255,0,0));
    light.setPixelColor(curOnLight + 3 % 24, light.Color(255,0,0));
    light.setPixelColor(curOnLight + 4 % 24, light.Color(255,0,0));
    light.setPixelColor(curOnLight + 5 % 24, light.Color(255,0,0));
    light.show();
    curOnLight += 6;
  }
  
  void patternEnd() {
  light.clear();
    curOnLight = 0;
  }
  
};

// Define Loading Pattern Class
class LoadingPattern {
  protected:
      Adafruit_NeoPixel light;
      int curOnLight = 0;
      long timeDelay = 100;
      long endTime;

  public:
      LoadingPattern() {}
      LoadingPattern(Adafruit_NeoPixel l) {
          light = l;
      }
      bool isActive = false;
      void process() {
          if (isActive) {
              if (millis() > endTime) {
                  patternInc();
                  endTime = millis() + timeDelay;
              }
          }
      }

      void patternStart() {
          light.clear();
          light.setPixelColor(curOnLight, (255, 0, 0));
          light.show();
          isActive = true;
          endTime = millis() + timeDelay;
      }

      void patternInc() {
        if(curOnLight == NEO_PIXEL_COUNT + 1) {
          curOnLight=0;
          light.clear();
        }
        light.setPixelColor(curOnLight, light.Color(255, 0, 0));
        light.show();
        curOnLight++;
      }
  
      void patternEnd() {
          light.clear();
          curOnLight = 0;
      }
};
// Define Rainbow Pattern
class RainbowPattern {
  protected:
    Adafruit_NeoPixel light;
    int curOnLight = 0;
    long timeDelay = 100;
    long endTime;
  public:
    RainbowPattern() {}
    RainbowPattern(Adafruit_NeoPixel l) {
      light = l;
    }
    bool isActive = false;
  void process() {
    if(isActive) {
      if(millis() > endTime) {
        patternInc();
        endTime = millis()+timeDelay;
      }
    }
  }

  
  void patternStart() {
  light.setPixelColor(curOnLight, (255,0,0));
    light.show();
    isActive = true;
  }
  
  void patternInc() {
    curOnLight = curOnLight % NEO_PIXEL_COUNT;   
    
    int r = random(0,255);
    int g = random(0,255);
    int b = random(0,255);
    
    light.setPixelColor(curOnLight, light.Color(r,g,b));
    light.setPixelColor(curOnLight + 1 % 24, light.Color(r,g,b));
    light.setPixelColor(curOnLight + 2 % 24, light.Color(r,g,b));
    light.setPixelColor(curOnLight + 3 % 24, light.Color(r,g,b));
    light.setPixelColor(curOnLight + 4 % 24, light.Color(r,g,b));
    light.setPixelColor(curOnLight + 5 % 24, light.Color(r,g,b));
    light.show();
    curOnLight += 6;
  }
    void patternEnd() {
    light.clear();
    }
};


// Define Box Side Class
class BoxSide {
  bool isActive = false;

    // Initialise Timers
  long servoTimerEndTime;
  long servoTimerLength = 1000;
  long servoReturnTimerLength = 500;
  bool servoTimerStarted;
    
  int lightPin;

  Servo servo;
  byte sensorPin;
  

  //Patterns
  SequentialPattern sqPat;
    ColumnsPattern coPat;
    LoadingPattern ldPat;
    RowPattern rwPat;
    RainbowPattern rbPat;
    bouncingPattern bPat;

  public:
      Adafruit_NeoPixel light;
    int activePatternNum = -3;
        BoxSide *neighbourSide;
    BoxSide(Servo sv, int l, byte sen) {
            servo = sv;
            lightPin = l;
            sensorPin = sen;
            //light = Adafruit_NeoPixel(NEO_PIXEL_COUNT, lightPin);
            light = leftLight;
            light.clear();
            patternSetup();
        }

  
  // Method to call process every frame
  void process() {
    processPattern();
        //If the sensor has not been triggered read sensor value
    if (!isActive) {
      if(analogRead(sensorPin) >= SENSITIVITY && neighbourSide->isActive != true) {
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
        patternStart(-1);
        //neighbourSide->patternExit();
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

  // Method to set the timer length
  void setTimer(int timerLength) {
    servoTimerEndTime = millis()+timerLength;
  }


  //Initialise all "Pattern" objects here
  void patternSetup() {
    sqPat = SequentialPattern(light);
        coPat = ColumnsPattern(light);
        ldPat = LoadingPattern(light);
        rwPat = RowPattern(light);
        rbPat = RainbowPattern(light);
        bPat = bouncingPattern(light);
  }
  
  //Call setup function (if exists) for pattern
    //Pass -2 for default pattern
    //-1 for random
    //Other for set value
  void patternStart(int genRnd) {
        light.clear();
      int patId = genRnd;
      if(genRnd == -1) {
      patId = random(PATTERNCOUNT);
      }
    switch(patId) {
          case 0:
        sqPat.patternStart();
            break;
            case 1:
              coPat.patternStart();
              break;
            case 2:
              rwPat.patternStart();
              break;
            case 3:
              ldPat.patternStart();
              break;
            case 4:
              rbPat.patternStart();
              break;
            case 5:
              bPat.patternStart();
              break;

        }
    this->activePatternNum = patId;
  }
  
  void processPattern() {
    switch(this->activePatternNum) {
      case 0:
        sqPat.process();
              break;
            case 1:
              coPat.process();
              break;
      case 2:
              rwPat.process();
              break;
            case 3:
              ldPat.process();
            break;
            case 4:
              rbPat.process();
              break;
            case 5:
              bPat.process();
              break;
        }
  }

    void patternExit() {
    switch(this->activePatternNum) {
          case 0:
        sqPat.patternEnd();
              break;
            case 1:
              coPat.patternEnd();
              break;
            case 2:
              rwPat.patternEnd();
              break;
            case 3:
              ldPat.patternEnd();
              break;
            case 4:
              rbPat.patternEnd();
              break;
            case 5:
              bPat.patternEnd();
              break;

        }
        this->activePatternNum = -3;
        light.fill(light.Color(255,0,255));
        light.show();
    }
};

const byte sensorPinLeft = A0;
const byte sensorPinRight = A1;

int lightPinsLeft = 8;
int lightPinsRight = 8;

int servoPinLeft = 5;
int servoPinRight = 6;

Servo leftServo;
Servo rightServo;

// Define left and right box-side variables
BoxSide leftSide(leftServo, lightPinsLeft, sensorPinLeft);
BoxSide rightSide(rightServo, lightPinsRight, sensorPinRight);

int x = 0;
// Define Setup Function
void setup(){
    leftLight.begin();
    randomSeed(analogRead(8));
    Serial.begin(4800);
  pinMode(lightPinsLeft, OUTPUT);
  pinMode(lightPinsRight, OUTPUT);

  leftServo.write(DEFAULT_SERVO_POS);
  rightServo.write(DEFAULT_SERVO_POS);
  leftServo.attach(servoPinLeft);
  rightServo.attach(servoPinRight);

  pinMode(sensorPinLeft, INPUT);
  pinMode(sensorPinRight, INPUT);
//  
    leftSide.neighbourSide = &rightSide;
    rightSide.neighbourSide = &leftSide;
}

// Define Loop Function
void loop() {
  leftSide.process();
  Serial.println(analogRead(A1));

  rightSide.process();
}
