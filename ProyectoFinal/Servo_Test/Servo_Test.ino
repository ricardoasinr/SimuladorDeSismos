#include <Servo.h>
Servo servo1;

int PULSOMIN = 850;
int PULSOMAX = 2150;

int VALORPOT;
int ANGULO;

void setup() {
  servo1.attach(5, PULSOMIN, PULSOMAX);
  Serial.begin(9600);
}

void loop() {

  VALORPOT = analogRead(A0);
  Serial.println(VALORPOT); //min 5, max 1017
  ANGULO= map(VALORPOT, 5, 1017, 0, 180);
  servo1.write(ANGULO);
  delay(20);
  
  
}
