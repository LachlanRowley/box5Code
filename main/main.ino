//#include <Servo.h>
//#include <Neopixel.h>
//#include <Adafruit_NeoPixel.h>
#include<Pattern.h>

// Define left and right box-side variables
BoxSide leftSide;
BoxSide rightSide;

const int SENSITIVITY = 250;
const int sensorPinLeft;
const int sensorPinRight;

int lightPinsUp[1] = {1};
int lightPinsDown[1] = {2};

int servoPinLeft = -1;
int servoPinRight = -1;

Servo leftServo;
Servo rightServo;


void setup(){
  Serial.begin(9600);
  // Set pins to output
  for(int i = 0; i < sizeof(LightPinsUp); i++){
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
  
