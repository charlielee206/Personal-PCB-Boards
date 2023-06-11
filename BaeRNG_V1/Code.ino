#include <avr/sleep.h>
#include <avr/interrupt.h>

byte numbers[10][7] = {
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1},
  {0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,0,0,0,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1}
};

const byte pins[7] = {10,9,8,7,6,5,4};
const byte ButtonPin = 3;
int ButtonState = 0;
unsigned long LastCheck = 0;

//==========FUNCTION DECLARATION DIVISION==========
void DisplayNumber(int);
void PlayWaitAnimation(int);
void Going_To_Sleep();
void wakeUp();

//==========SETUP DIVISION==========
void setup() {
  for(int i = 0; i <= 6; i++){
    pinMode(pins[i], OUTPUT);
  }
  pinMode(ButtonPin, INPUT_PULLUP);
  PlayWaitAnimation(2);
  DisplayNumber(8);
  randomSeed(analogRead(0));
}

void DisplayNumber(int InputValue){
  for(int i = 0; i <= 6; i++){
    digitalWrite(pins[i], numbers[InputValue][i]);
    delay(1);
  }
}

void PlayWaitAnimation(int iterations){
  for(int i = 0; i <= 6; i++){
    digitalWrite(pins[i], 0);
  }
  for(int i = 1; i <= iterations; i++){
    digitalWrite(pins[5],0);
    digitalWrite(pins[0],1);
    delay(70);
    digitalWrite(pins[0],0);
    digitalWrite(pins[1],1);
    delay(70);
    digitalWrite(pins[1],0);
    digitalWrite(pins[2],1);
    delay(70);
    digitalWrite(pins[2],0);
    digitalWrite(pins[3],1);
    delay(70);
    digitalWrite(pins[3],0);
    digitalWrite(pins[4],1);
    delay(70);
    digitalWrite(pins[4],0);
    digitalWrite(pins[5],1);
    delay(70);
  }
}

void Going_To_Sleep(){
  delay(10);
    for(int i = 0; i <= 6; i++){
    digitalWrite(pins[i], 0);
  }
  sleep_enable();
  attachInterrupt(1, wakeUp, HIGH);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  delay(100);
  sleep_cpu();
}

void wakeUp(){
  sleep_disable();
  detachInterrupt(1);
}



void loop() {
  if(digitalRead(ButtonPin) == HIGH){
    while(digitalRead(ButtonPin) == HIGH){
      delay(10);
    }
    PlayWaitAnimation(4);
    DisplayNumber(random(1,6));
    LastCheck = millis();
  }
  if(millis() < LastCheck){
    LastCheck = 0;
  }
  
  if((millis() - LastCheck)> 10000){
    Going_To_Sleep();
  }

}
