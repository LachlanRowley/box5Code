#include<Pattern.h>

class Pattern::Pattern {
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

