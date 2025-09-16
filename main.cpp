#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
}
class mytimer
{
  public:
  void start()
  {
    starttime=millis();
    hasstarted=true;
  }
  unsigned long gettime()
  {
    return millis()-starttime;
  }
  bool hasstarted=false;
  private:
  unsigned long starttime;
};
mytimer mytime;
mytimer blinkTimer;
mytimer blinkDuration;

bool blinking = false;
bool ledState = false;
bool switch1Active = false;
bool lastSwitch1State = false;

void loop() {
  // put your main code here, to run repeatedly:
 bool switchState1 = digitalRead(A0);
 bool switchState2 = digitalRead(A1);
 bool switchState3 = digitalRead(A2);
 bool switchState4 = digitalRead(A3);
if (switchState1 && !lastSwitch1State) {
  if(!switch1Active) {
    switch1Active = true;
    counter = 1;
     digitalWrite(5, HIGH);
    mytime.start();
  } 
  else {
    counter = 0;
    blinking = false;
    switch1Active = false; 
     mytime.hasstarted = false;

    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
 }
}
lastSwitch1State = switchState1;

if (counter == 1 && switchState2 && mytime.gettime()>3000 && mytime.hasstarted) {
    counter = 2;
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
}  
  if (counter == 2 && switchState3 && !blinking) {
  digitalWrite(6, LOW);
  blinking = true;
  blinkTimer.start();
  blinkDuration.start();
  ledState = false;
  digitalWrite(9,LOW);
  }
  if (blinking){
    if (blinkDuration.gettime() >= 5000){
      blinking = false;
      digitalWrite(9, LOW);
      counter = 3;
    }
      else {
      if (blinkTimer.gettime() >= 250){
        ledState = !ledState;
        digitalWrite(9, ledState ? HIGH : LOW);
        blinkTimer.start();
       }
      }
    }
  
  if (counter == 3 && switchState4) {
    digitalWrite(10, HIGH);
  }
}
