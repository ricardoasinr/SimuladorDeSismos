String s; 
char x;

void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}
 
void loop(){

   //digitalWrite(13, HIGH);
   while(Serial.available()>0){
      delay(10);
      x = Serial.read(); 
      s+=x;
   }
   if(s.length() > 0){
    Serial.println(s); 
   }
   if(s=="Hola"){
    digitalWrite(13, HIGH);
   }
   if(s=="Chau"){
    digitalWrite(13, LOW
    +++++++++);
   }
   s="";
}
 
