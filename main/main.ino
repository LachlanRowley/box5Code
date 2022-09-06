//#include <Servo.h>
//#include <Neopixel.h>
//#include <Adafruit_NeoPixel.h>
#include<Pattern.h>

// Define left and right box-side variables
BoxSide leftSide;
BoxSide rightSide;


void setup(){

  // Initialise LED and servo pins
  int LightPins[2] = {1, 4};
  int ServoPins[2] = {2, 3};

  int LEFT_SENSOR_PIN;
  int RIGHT_SENSOR_PIN;


  // Set pins to output
  for(int i = 0; i < sizeof(LightPins); i++){
    pinMode(i, OUTPUT);
  }

  // Set pins to input
  for(int i = 0; i < sizeof(ServoPins); i++){
    pinMode(i, INPUT);
  }
  
  //Interrupt triggers when sensor reads HIGH from LOW
  //attachInterrupt(digitalPinToInterrupt(LEFT_SENSOR_PIN), leftSide.onSensorTrigger, RISING);
  //attachInterrupt(digitalPinToInterrupt(RIGHT_SENSOR_PIN), rightSide.onSensorTrigger, RISING);
}

void loop() {
  if(analogueRead(PINLEFT) <= MIN_VALUE) {
    leftSide.onSensorTrigger();
  }
  leftSide.process();
  rightSide.process();
}
  /*
  
  if (left LED is primary){
    display primary LED pattern left;
    display base LED pattern right;
  }
  else if (right LED is primary){
    display primary LED pattern right;
    display base LED pattern left;
  }
  else{
    display base LED pattern
  }

  */
  
