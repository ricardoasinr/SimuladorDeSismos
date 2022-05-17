#include <Servo.h>
Servo servo1;
Servo servo2;

void setup() {
  servo1.attach(5);
  servo2.attach(6);
  Serial.begin(9600);
}

void loop() {

  //VALORPOT = analogRead(A0);
  //Serial.println(VALORPOT); //min 5, max 1017
  //ANGULO= map(VALORPOT, 0, 1023, 0, 200);
  //servo1.write(ANGULO);
  //delay(1000);
  for(int k=90; k<=270; k++){
    servo1.write(k);
    delay(1);
    
  }
  for(int k=90; k<=270; k++){
    servo2.write(k);
    delay(1);
    
  }
  
}
