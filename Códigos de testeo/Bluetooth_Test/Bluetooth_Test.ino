String s; 
char x;

void setup(){
  Serial.begin(9600);
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
   s="";
}
 
