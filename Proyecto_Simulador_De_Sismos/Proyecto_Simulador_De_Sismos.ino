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


int intensidad;
int tiempo;

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

int  menu_intensidad(){
  
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
  
  tecla = teclado.getKey();
  if (tecla){

    delay(10);
    
      if(tecla=='1'){
        return 5;    
      }
      else if(tecla=='2'){
        return 4;
      }
      else if(tecla == '3'){

        return 3;
      }
      else if(tecla== '4'){

        return 4;
      }
    }  
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
  
  do{
    
    tecla = teclado.getKey();
    if(tecla){

    delay(10);
    
      if(tecla=='1'){
        return 15;    
      }
      else if(tecla=='2'){
        return 30;
      }
      else if(tecla == '3'){

        return 45;
      }
      else if(tecla== '4'){

        return 60;
      }
    }  
  }
  while(not tecla);

}

void  menu_principal(){

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.setTextSize(2);
  oled.println("  MODO DE OPERACIÓN");
  oled.println("");
  oled.setTextSize(1);
  oled.println("1.  Bluetooth");  
  oled.println("");
  oled.println("2.  Manual");
  oled.println("");
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
   tecla = teclado.getKey();
    
   if (tecla){

     delay(10);
    
     if(tecla=='1'){

       // MODO BLUETOOTH
          
      
      }
      
      else if(tecla=='2'){

      intensidad = menu_intensidad();
      tiempo = menu_tiempo();

    
      }
    }  
  }
  
 else{
    
    off();
    
  }
}
