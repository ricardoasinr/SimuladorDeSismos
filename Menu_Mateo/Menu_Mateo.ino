#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Servo.h>
Servo servo1;
Servo servo2;

#include <Adafruit_GFX.h>   // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>   // libreria para controlador SSD1306 
#define ANCHO 128     // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64       // reemplaza ocurrencia de ALTO por 64
#define OLED_RESET 20      // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto

#include <Keypad.h> // importa o incluye la libreria Keypad
const byte FILAS=2;
const byte COLUMNAS=4;
char keys[FILAS][COLUMNAS]= 
{    
  {'1','2', '3', 'A'},
  {'4','5', '6', 'B'}
};
byte pinesFilas[FILAS]= {8,9};
byte pinesColumnas[COLUMNAS]= {10,11,12,13};
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);
char tecla;
char aux;

int sw;
#define sw1 7

int buzzer_pin= 2;

int intensidad = 0;
int duracion = 0;
unsigned int fin=0;
unsigned int t=0;
unsigned int factor = 0;
float val_intensidad = 0;

String s; 
char x;


// AREA DE SUBPROGRAMAS PARA MEL MENU

void menu_bt(){

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.setTextSize(1);
  oled.print("- Manejo Bluetooth -");
  oled.setCursor(0,25);
  oled.print("[ Ingrese comandos ]");
  oled.setCursor(0,35);
  oled.print("[       de voz     ]");
  oled.display();   
}

void menu_manual(){
  
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(10,0);
  oled.setTextSize(1);
  oled.println("-- Manejo manual --");
  oled.setTextSize(1);
  oled.setCursor(0,18);
  oled.print("1.  Intensidad");
  oled.setCursor(0,30);
  oled.print("2.  Duracion");
  oled.setCursor(0,42);
  oled.print("3.  Parametros");
  oled.setCursor(0,54);
  oled.print("B.  Simular");
  oled.display();
}

void menu_intensidad(){

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(10,0);
  oled.setTextSize(1);
  oled.print("    Intensidad");
  oled.setCursor(0, 20);
  oled.print("1. M2      3. M5");
  oled.setCursor(0, 34);
  oled.print("2. M3,5    4. M7");
  oled.setCursor(0, 56);
  oled.print("A. Volver");
  oled.display();
}

void  menu_duracion(){
  
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(10,0);
  oled.setTextSize(1);
  oled.print("    Duracion");
  oled.setCursor(0, 20);
  oled.print("1. 15s      3. 45s");
  oled.setCursor(0, 38);
  oled.print("2. 30s      4. 60s");
  oled.setCursor(0, 56);
  oled.print("A. Volver");
  oled.display();
}

void sonido(){

  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
  
}

void muestra_parametros(int val_intesidad, int duracion){

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(6, 0);
  oled.setTextSize(1);
  oled.print("Parametros de sismo");
  oled.setCursor(0, 22);
  
  if(val_intensidad == 0 && duracion == 0){
    
    oled.print("Intensidad: N/A");
    oled.setCursor(0, 38);
    oled.print("Duracion: N/A");
  }
  else if(val_intensidad != 0 && duracion == 0){

    oled.print("Intensidad: "); oled.print("M "); oled.print(val_intensidad);
    oled.setCursor(0, 38);
    oled.print("Duracion: N/A");
  }
  else if(val_intensidad == 0 && duracion != 0){
   
    oled.print("Intensidad: N/A");
    oled.setCursor(0, 38);
    oled.print("Duracion: "); oled.print(duracion); oled.print('s');
  }
  else{
    oled.print("Intensidad: "); oled.print("M "); oled.print(val_intensidad);
    oled.setCursor(0, 38);
    oled.print("Duracion: "); oled.print(duracion); oled.print('s');
  }
  oled.setCursor(0, 56);
  oled.print("A.  Volver");
  oled.display();
}

void simulacion(int intensidad){
  
    for(int k=0; k<= 110; k++){
      servo2.write(k); servo1.write(k); 
      delay(intensidad);
    }
}

void volver(){
  sonido();
  tecla='X'; 
}

void sismo_en_curso(){

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(10,30);
  oled.setTextSize(1);
  oled.print("SISMO EN CURSO");
  oled.display();
}

int factor_tiempo(int intensidad){
  
  switch(intensidad){

    case 4: return 125;
    case 3: return 90;
    case 2: return 60;
    case 1: return 30;
  }
}

void setup() { 
  
  Serial.begin(9600);
  Wire.begin();         // inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializa pantalla con direccion 0x3C
  oled.clearDisplay();
  oled.display();
  servo1.attach(5); servo2.attach(6);
  pinMode(4, OUTPUT);
  }
 
void loop() {

  //Serial.println(sw);
  sw = digitalRead(sw1);
  
  if(sw==0){

    menu_manual();
    tecla = teclado.getKey();

    if(tecla){
      sonido();
   
    while(tecla=='1'){

       
       menu_intensidad();
       aux = teclado.getKey();

       switch(aux){

              case '1' : sonido();intensidad = 4; val_intensidad = 2; break;
              case '2' : sonido();intensidad = 3; val_intensidad = 3.5; break;
              case '3' : sonido();intensidad = 2; val_intensidad = 5; break;
              case '4' : sonido();intensidad = 1; val_intensidad = 7; break;
              case 'A' : volver(); break;
          }
    }
    
    while(tecla=='2'){

       menu_duracion();
       aux = teclado.getKey();

       switch(aux){

              case '1' : sonido(); duracion = 15; fin=duracion*155; break;
              case '2' : sonido(); duracion = 30; fin=duracion*157;break;
              case '3' : sonido(); duracion = 45; fin=duracion*160;break;
              case '4' : sonido(); duracion = 60; fin=duracion*162;break;
              case 'A' : volver(); break;
      }      
    }
    
    while(tecla=='3'){

        muestra_parametros(val_intensidad, duracion);
        aux = teclado.getKey();

        if(aux=='A'){

          volver();
        }
      }
      while(tecla=='B'){

        sismo_en_curso();
        factor = factor_tiempo(intensidad); Serial.println(factor);
        while(t  <=  fin){

          simulacion(intensidad);
          t+=factor;
      }   
      factor = 0;
      t=0;
      duracion=0;
      intensidad=0;
      val_intensidad=0;
      volver();
    }
  }
 }
  else{

      menu_bt();
      while(Serial.available()>0){
      
         delay(10);
         x = Serial.read(); 
         s+=x;
      }
      if(s.length() > 0){

         s.toLowerCase();
         Serial.println(s);
         
         if(s=="modo 1"){

            intensidad = 4; 
            duracion = 15;
            fin=duracion*160;
            sismo_en_curso();
            factor = factor_tiempo(intensidad);
            while(t  <=  fin){

              simulacion(intensidad);
              t+=factor;
            }
            t=0;   
         }
         if(s=="modo 2"){
          
           intensidad = 3; 
           duracion = 15;
           fin=duracion*160;
           sismo_en_curso();
           factor = factor_tiempo(intensidad);
           while(t  <=  fin){

              simulacion(intensidad);
              t+=factor;
           }   
           t=0;
         }
         
         if(s=="modo 3"){
           intensidad = 2; 
           duracion = 15;
           fin=duracion*160;
           sismo_en_curso();
           factor = factor_tiempo(intensidad);
           while(t  <=  fin){

              simulacion(intensidad);
              t+=factor;
           }
           t=0;   
         }
         
         if(s=="modo 4"){
            
           intensidad = 1; 
           duracion = 30;
           fin=duracion*166;
           sismo_en_curso();
           factor = factor_tiempo(intensidad);
           while(t  <=  fin){

              simulacion(intensidad);
              t+=factor;
           }
           t=0;
          }
    }
    s="";
  }
}
