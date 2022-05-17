String s; 
char x;
#include<Servo.h>
Servo servo1;

void setup(){
  Serial.begin(9600);
  servo1.attach(5);
}
 
void loop(){
  
   while(Serial.available()>0){
      delay(10);
      x = Serial.read(); 
      s+=x;
   }
   if(s.length() > 0){
    Serial.println(s); 
   }
   while(s=="fuerte"){
    for(int k=0; k<=180; k++){
      servo1.write(k);
      delay(1);
      break;
    
     }
   }
   while(s=="suave"){
    for(int k=0; k<=180; k++){
      servo1.write(k);
      delay(3);
      break;
    }
   }
   s="";
}
 
