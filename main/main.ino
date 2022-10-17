// Import Libraries
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// Initialise Servo Variables
const int DEFAULT_SERVO_POS = 0;
const int SERVO_END_POS = 90;
const int NEO_PIXEL_COUNT = 24;
const int SENSITIVITY = 950;


const int PATTERNCOUNT = 3;
// Define Pattern Class
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
        light.setPixelColor(curOnLight, (255, 0, 0));
        light.show();
        isActive = true;
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

//Loading Pattern
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
        light.setPixelColor(curOnLight, (255, 0, 0));
        light.show();
        isActive = true;
    }

    void patternInc() {
        curOnLight = curOnLight % NEO_PIXEL_COUNT;

        light.setPixelColor(curOnLight, light.Color(255, 0, 0));
        light.show();
        curOnLight++;
    }
    void patternEnd() {
		light.clear();
      	curOnLight = 0;
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
	Adafruit_NeoPixel light;

	Servo servo;
	byte sensorPin;

  
	int activePatternNum = -1;

	//Patterns
	SequentialPattern sqPat;
  	ColumnsPattern coPat;
  	LoadingPattern ldPat;

	public:
        BoxSide *neighbourSide;
		BoxSide(Servo sv, int l, byte sen) {
            servo = sv;
            lightPin = l;
            sensorPin = sen;
            light = Adafruit_NeoPixel(NEO_PIXEL_COUNT, lightPin);
            light.begin();
            light.clear();
            patternSetup();
        }

  
	// Method to call process every frame
	void process() {
		processPattern();
      	//If the sensor has not been triggered read sensor value
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
      	patternStart(-1);
      	neighbourSide->patternStart(-2);
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
	}
	
	//Call setup function (if exists) for pattern
  	//Pass -2 for default pattern
  	//-1 for random
  	//Other for set value
	void patternStart(int genRnd) {
    	int patId = genRnd;
	    if(genRnd == -1) {
			patId = random(PATTERNCOUNT);
    	}
      	patternExit();
		switch(patId) {
          	case -2:
          		ldPat.patternStart();
          		break;
	        case 0:
				sqPat.patternStart();
		        break;
          	case 1:
          		coPat.patternStart();
          		break;
		}
		activePatternNum = patId;
	}
	
	void processPattern() {
        switch(activePatternNum) {
            case -2:
          		ldPat.process();
          		break;
			case 0:
				sqPat.process();
       	        break;
            case 1:
                coPat.process();
                break;
        }
  }

  	void patternExit() {
		switch(activePatternNum) {
          	case -2:
          		ldPat.patternEnd();
          		break;
	          case 0:
				sqPat.patternEnd();
          		break;
            case 1:
          		coPat.patternEnd();
          		break;
        }
    }
};

const byte sensorPinLeft = A0;
const byte sensorPinRight = -1;

int lightPinsLeft = 2;
int lightPinsRight = -1;

int servoPinLeft = 10;
int servoPinRight = -1;

Servo leftServo;
Servo rightServo;

// Define left and right box-side variables
BoxSide leftSide(leftServo, lightPinsLeft, sensorPinLeft);
BoxSide rightSide(rightServo, lightPinsRight, sensorPinRight);

// Define Setup Function
void setup(){
	Serial.begin(9600);
	pinMode(lightPinsLeft, OUTPUT);
	pinMode(lightPinsRight, OUTPUT);

	leftServo.write(DEFAULT_SERVO_POS);
	rightServo.write(DEFAULT_SERVO_POS);
	leftServo.attach(servoPinLeft);
	rightServo.attach(servoPinRight);

	pinMode(sensorPinLeft, INPUT);
	pinMode(sensorPinRight, INPUT);
  
	leftSide.neighbourSide = &rightSide;
	rightSide.neighbourSide = &leftSide;   
}

// Define Loop Function
void loop() {
	leftSide.process();
	rightSide.process();
}
