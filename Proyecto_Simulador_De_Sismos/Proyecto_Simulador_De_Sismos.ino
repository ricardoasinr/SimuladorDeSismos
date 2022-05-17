#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h> 
#define ANCHO 128 
#define ALTO 64    
#define OLED_RESET 4  
#include <Keypad.h> 
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET); 

int sw;
#define sw1 A0
#define buzzer_pin 13 

const byte FILAS=2;
const byte COLUMNAS=4;
char keys[FILAS][COLUMNAS]= { 
  {'1','2','3','A'},
  {'4','5','6','B'}
};
byte pinesFilas[FILAS]= {8,9};
byte pinesColumnas[COLUMNAS]= {10,11,12,13};
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);
char tecla;

void off(){
  
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(25, 15);
  oled.setTextSize(2);
  oled.print("Sistema");
  oled.setCursor(25, 35);
  oled.setTextSize(2);
  oled.print("Apagado");
  oled.display();
}

void  menu_intensidad(){
  
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(5, 0);
  oled.setTextSize(2);
  oled.println("INTENSIDAD");
  oled.setTextSize(1);
  oled.println("");
  oled.println("1. (M2)     3.(M5)");
  oled.println("");
  oled.println("2. (M3,5)   4.(M7)");
  oled.println("");
  oled.println("A. Volver  M=Magnitud");
  oled.display();
}

void  menu_tiempo(){
  
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(5, 0);
  oled.setTextSize(2);
  oled.println("--TIEMPO--");
  oled.setTextSize(1);
  oled.println("");
  oled.println("1. 15s     3. 45s");
  oled.println("");
  oled.println("2. 30s     4. 1min");
  oled.println("");
  oled.println("A. Volver");
  oled.display();
}

void  menu_principal(){

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.setTextSize(2);
  oled.println("---MENU---");
  oled.println("");
  oled.setTextSize(1);
  oled.println("1.  Intensidad");  
  oled.println("");
  oled.println("2.  Tiempo");
  oled.println("");
  oled.display();
}

void  aviso(){
  
   oled.clearDisplay();
   oled.setTextColor(WHITE);
   oled.setCursor(0, 0);
   oled.setTextSize(2);
   oled.println("  AVISO!!");
   oled.println("");
   oled.setTextSize(1);
   oled.println(" Tiempo e intensidad");
   oled.println(" requerida antes de");
   oled.println("iniciar la simulacion");
   oled.display();
}

void sonido_M2(){

  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
}

void sonido_M3_5(){

  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin); 
}

void sonido_M5(){

  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
}

void sonido_M7(){

  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
}

void volver(){
  
  tecla='X';
}

void setup() { 

  Serial.begin(9600);
  Wire.begin();        
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  oled.clearDisplay();
  oled.display();
}
 
void loop() {
  
  sw = digitalRead(sw1);
  
  if(sw==1){
    
    menu_principal();
    tecla=teclado.getKey();
    
    if (tecla){

     delay(10);
    
     while(tecla=='1'){

        
        menu_intensidad();
        char aux = teclado.getKey();  
        
        switch(aux){  
        
        case '1': break; 

        case '2': break; 

        case '3': break; 

        case '4': break; 
      
        case 'A': volver(); break; 
      
        }
      }
    
      while(tecla=='2'){

        menu_tiempo();
        char aux =teclado.getKey();

        switch(aux){

          case '1':  break;

          case '2':  break;

          case '3':  break;

          case '4':  break;

          case 'A': volver(); break;
      
        }
      }
    }  
  }
  
 else{
    
    off();
    
  }
}
