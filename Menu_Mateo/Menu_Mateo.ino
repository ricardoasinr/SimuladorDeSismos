#include <Adafruit_GFX.h>   // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>   // libreria para controlador SSD1306 
#define ANCHO 128     // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64       // reemplaza ocurrencia de ALTO por 64
#define OLED_RESET 4      // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto

bool correr;
int velocidad=0;
int ledrojo_pin = 8;
int ledamarillo_pin = 7;
int ledverde_pin = 6;
int buzzer_pin= 2;
int IN1_pin = 4;      // IN1_pin de L298N a pin digital 2
int IN2_pin = 3;      // IN2_pin de L298N a pin digital 3
int ENA_pin = 5;      // ENA_pin de L298N a pin digital 5
int sw;
#define sw1 A0

#include <Keypad.h> // importa o incluye la libreria Keypad
const byte FILAS=1;
const byte COLUMNAS=4;
char keys[FILAS][COLUMNAS]= 
{    
  {'1','2', '3', 'A'},
};
byte pinesFilas[FILAS]= {13};
byte pinesColumnas[COLUMNAS]= {12,11,10,9};
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);
char tecla;



// AREA DE SUBPROGRAMAS PARA MEL MENU



void menu_inicial(){

    digitalWrite(ledverde_pin, HIGH);
    oled.clearDisplay();
    oled.setTextColor(WHITE);   // establece color al unico disponible (pantalla monocromo)
    oled.setCursor(0, 0);     // ubica cursor en inicio de coordenadas 0,0
    oled.setTextSize(1);      // establece tamano de texto en 1
    oled.print("1. Estado");
    oled.setCursor(0, 15);
    oled.print("2. Velocidad");
    oled.setCursor(0, 30);
    oled.print("3. Sentido de giro");
    oled.display(); 
    
}

void menu_apagado(){

  oled.clearDisplay();
  oled.setTextColor(WHITE);   
  oled.setCursor(0, 30);     
  oled.setTextSize(1);      
  oled.print("Sistema: Apagado");
  oled.display();
  digitalWrite(ledrojo_pin, LOW);
  digitalWrite(ledamarillo_pin, LOW);
  digitalWrite(ledverde_pin, LOW);
  analogWrite(ENA_pin, LOW);
  
}

void volver(){

  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
  tecla='X';
  
}

void sonido(){

  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
  
}

void menu_1(){

    oled.clearDisplay();
    oled.setTextColor(WHITE);   // establece color al unico disponible (pantalla monocromo)
    oled.setCursor(0, 0);     // ubica cursor en inicio de coordenadas 0,0
    oled.setTextSize(1);      // establece tamano de texto en 1
    oled.print("1. Marcha");
    oled.setCursor(0, 15);
    oled.print("2. Parada");
    oled.setCursor(0, 30);
    oled.print("A. Volver");
    oled.display(); 
    
}

bool marcha(int velocidad){

  digitalWrite(ledrojo_pin, HIGH);
  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin); 
  if(velocidad==0){
    analogWrite(ENA_pin, 77);
  }
  else{
    analogWrite(ENA_pin, velocidad);
  }
  return true;
}

bool parada(){

  digitalWrite(ledrojo_pin, LOW);
  analogWrite(ENA_pin, 0);
  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
  return false;
    
}

void menu_2(){

    oled.clearDisplay();
    oled.setTextColor(WHITE);   
    oled.setCursor(0, 0);     
    oled.setTextSize(1);      
    oled.print("1. 30%");
    oled.setCursor(0, 15);
    oled.print("2. 60%");
    oled.setCursor(0, 30);
    oled.print("3. 100%");
    oled.setCursor(0, 45);
    oled.print("A. Volver");
    oled.display(); 
  
}

int vel_1(bool correr){

  velocidad = 77;
  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
  if(correr==true){
    analogWrite(ENA_pin, 77);
  }
  return velocidad;
  
}

int vel_2(bool correr){

  velocidad=156;
  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin); 
  if(correr==true){
    analogWrite(ENA_pin, 156);
  }
  return velocidad;
  
}

int vel_3(bool correr){

  velocidad = 255;
  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
  if(correr==true){
    analogWrite(ENA_pin, 255);
  }
  return velocidad;
}

void menu_3(){

    oled.clearDisplay();
    oled.setTextColor(WHITE);   
    oled.setCursor(0, 0);     
    oled.setTextSize(1);      
    oled.print("1. Izquierda");
    oled.setCursor(0, 15);
    oled.print("2. Derecha");
    oled.setCursor(0, 30);
    oled.print("A. Volver");
    oled.display(); 
  
}

void izq(){

    sonido();
    digitalWrite(ledamarillo_pin, LOW);
    digitalWrite(IN1_pin, HIGH);        
    digitalWrite(IN2_pin, LOW);
}

void der(){

    sonido();
    digitalWrite(ledamarillo_pin, HIGH);
    digitalWrite(IN1_pin, LOW);        
    digitalWrite(IN2_pin, HIGH);
}


void setup() { 
  
  Serial.begin(9600);
  Wire.begin();         // inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializa pantalla con direccion 0x3C
  oled.clearDisplay();
  oled.display();
  pinMode(ledrojo_pin, OUTPUT);
  pinMode(ledamarillo_pin, OUTPUT);
  pinMode(ledverde_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(IN1_pin, OUTPUT);
  pinMode(IN2_pin, OUTPUT);
  pinMode(ENA_pin, OUTPUT);

}
 
void loop() {

// LECTURAS Y ESCRITURAS DE PUERTOS

  sw = digitalRead(sw1);
  
  if(sw==1){
    
    menu_inicial();
    tecla= teclado.getKey();
    
    if (tecla){

     sonido();
     delay(10);
    
     while(tecla=='1'){

        
        menu_1();
        char aux = teclado.getKey();  
        
        switch(aux){  
        
        case '1': correr = marcha(velocidad); break; 

        case '2': correr = parada(); break; 
      
        case 'A': volver(); break; 
      
        }
      }
    
      while(tecla=='2'){

        menu_2();
        char aux =teclado.getKey();

        switch(aux){

          case '1': velocidad = vel_1(correr); break;

          case '2': velocidad = vel_2(correr); break;

          case '3': velocidad = vel_3(correr); break;

          case 'A': volver(); break;
      
        }
      }

      while(tecla=='3'){

        
        menu_3();
        char aux =teclado.getKey();

        switch(aux){

          case '1': izq(); break;

          case '2': der(); break;
      
          case 'A': volver(); break;
        
        }
      }
    }
      
  }
  
 else{
    
    menu_apagado();
    
  }
}
