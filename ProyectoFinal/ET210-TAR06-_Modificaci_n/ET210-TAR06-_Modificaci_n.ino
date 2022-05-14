
//////////////////////////////////////////////////////
#include <Adafruit_GFX.h>   // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>   // libreria para controlador SSD1306 
#define ANCHO 128     // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64       // reemplaza ocurrencia de ALTO por 64
#define OLED_RESET 4      // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto

/////////////////////////////////////////////////2//////

int potenciometro_pin = A0;    // select the input pin for the potentiometer
int ledrojo_pin = 8;
int ledamarillo_pin = 7;
int ledverde_pin = 6;
int buzzer_pin= 2;
int IN1_pin = 4;      // IN1_pin de L298N a pin digital 2
int IN2_pin = 3;      // IN2_pin de L298N a pin digital 3
int ENA_pin = 5;      // ENA_pin de L298N a pin digital 5
int velocidad = 0;  // variable to store the value coming from the sensor
int estadomotor = 0; // 0 apagado, 1 encendido
int estadosentidogiro = 0; // 0 izquierda, 1 derecha
int estadosistema = 0; // 0 apagado, 1 encendido
int sw;
#define sw1 13

///////////////////////////////////////////////////////
#include <Keypad.h> // importa o incluye la libreria Keypad
const byte FILAS=3;
const byte COLUMNAS=2;
char keys[FILAS][COLUMNAS]= {    // define la distribucion de teclas
  {'1','2'},
  {'4','5'}, 
  {'7','8'},
};
byte pinesFilas[FILAS]= {13,12,11};
byte pinesColumnas[COLUMNAS]= {10,9};
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);
char tecla;
///////////////////////////////////////////////////////


void setup() { 
  //////////////////////////////////////
  Serial.begin(9600);
  Wire.begin();         // inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializa pantalla con direccion 0x3C
  oled.clearDisplay();
  oled.display();
  //////////////////////////////////////
 
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
  
  sw=digitalRead(sw1);
  
  if(sw==1){
    estadosistema = 1;
  }
  else{
    estadosistema = 0;
    estadomotor = 0;
    estadosentidogiro = 0;
  }
  
  if (estadosentidogiro==0)
  { digitalWrite(ledamarillo_pin, LOW); }
  else { digitalWrite(ledamarillo_pin, HIGH); }

  if (estadomotor==0)
  { digitalWrite(ledrojo_pin, LOW); }
  else { digitalWrite(ledrojo_pin, HIGH); }

  if (estadosistema==0){ 
    digitalWrite(ledverde_pin, LOW); 
  }
  else { 
    digitalWrite(ledverde_pin, HIGH); 
  }
 
  velocidad = analogRead(potenciometro_pin); 
  velocidad = map(velocidad,0,1024,0,256);


// INFORMACION EN PANTALLA

  if (estadosistema==0)
  { 
    oled.clearDisplay();
    oled.setTextColor(WHITE);   // establece color al unico disponible (pantalla monocromo)
    oled.setCursor(0, 30);     // ubica cursor en inicio de coordenadas 0,0
    oled.setTextSize(1);      // establece tamano de texto en 1
    oled.print("Sistema: Apagado");
    oled.display(); 
  }
  else
  {
    oled.clearDisplay();
    oled.setTextColor(WHITE);   // establece color al unico disponible (pantalla monocromo)
    oled.setCursor(0, 0);     // ubica cursor en inicio de coordenadas 0,0
    oled.setTextSize(1);      // establece tamano de texto en 1
    oled.print("Sistema: Encendido");
    oled.setCursor(0, 15);
    if (estadomotor==0)
    { oled.print("Motor: Apagado"); }
    else { oled.print("Motor: Encendido"); }
    oled.setCursor(0, 30);
    if (estadosentidogiro==0)
    { oled.print("Sentido: Izquierda"); }
    else { oled.print("Sentido: Derecha"); }
    oled.setCursor(0, 45);
    oled.print("Velocidad: ");
    oled.print(velocidad);

    oled.display(); 
  }

// CONTROL DE MOTOR

  
  if (estadomotor==0)
  { digitalWrite(ENA_pin, LOW); }
  else
  {
     analogWrite(ENA_pin, velocidad);
  }
  if (estadosentidogiro==0)
    {
              
        digitalWrite(IN1_pin, HIGH);        
        digitalWrite(IN2_pin, LOW);       
    }
    else
    {
              
        digitalWrite(IN1_pin, LOW);        
        digitalWrite(IN2_pin, HIGH);       
    }
 
  
// TECLADO MATRICIAL Y BUZZER
 tecla= teclado.getKey(); // obtiene tecla presionada y asigna el valor a TECLA  
  if (tecla)
  {
    Serial.println(tecla);
    delay(10);
    switch (tecla)
    {
      /*case '1':       
        estadosistema = 1;
        tone(buzzer_pin, 1500);
        delay(200);
        noTone(buzzer_pin);
        break;
        
      case '2':
        estadosistema = 0;
        estadomotor = 0;
        estadosentidogiro = 0;
        tone(buzzer_pin, 1500);
        delay(200);
        noTone(buzzer_pin);
        break;
      */  
      case '4':
        if (estadosistema==1)
        {
          estadomotor = 1;
          tone(buzzer_pin, 1700);
          delay(200);
          noTone(buzzer_pin);
        }
        break;

      case '5':
        if (estadosistema==1)
        {
          estadomotor = 0;
          tone(buzzer_pin, 1700);
          delay(200);
          noTone(buzzer_pin);
        }
        break;
      
      case '7':
        if (estadosistema==1)
        {
          estadosentidogiro = 0;
          tone(buzzer_pin, 2000);
          delay(200);
          noTone(buzzer_pin);
          delay(200);
          tone(buzzer_pin, 2000);
          delay(200);
          noTone(buzzer_pin);
        }
        break;
      
      case '8':
        if (estadosistema==1)
        {
          estadosentidogiro = 1;
          tone(buzzer_pin, 2000);
          delay(200);
          noTone(buzzer_pin);
          delay(200);
          tone(buzzer_pin, 2000);
          delay(200);
          noTone(buzzer_pin);
        }
        break;
  
      default: 
        break;      
    }
   } 
}
