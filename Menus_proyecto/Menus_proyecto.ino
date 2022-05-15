
//////////////////////////////////////////////////////
#include <Adafruit_GFX.h>   // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>   // libreria para controlador SSD1306 
#define ANCHO 128     // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64       // reemplaza ocurrencia de ALTO por 64
#define OLED_RESET 4      // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto



/////////////////////////////////////////////////2//////
int ledrojo_pin = 8;
int ledamarillo_pin = 7;
int ledverde_pin = 6;

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

}
//MENUS
/*void buzzer()
{
  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
}
*/


void off()
{
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(25, 15);
  oled.setTextSize(2);
  oled.print("Sistema");
  oled.setCursor(25, 35);
  oled.setTextSize(2);
  oled.print("Apagado");
  oled.display();
  digitalWrite(ledrojo_pin, LOW);
  digitalWrite(ledverde_pin, LOW);
  digitalWrite(ledamarillo_pin, LOW);


}
void  menuINT()
{
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(5, 0);
  oled.setTextSize(2);
  oled.println("INTENSIDAD");
  oled.setTextSize(1);
  oled.println("");
  oled.println("1.   1");
  oled.println("2.   2");
  oled.println("3.   3");
  oled.println("4.   4");
  oled.display();
}

void  menutiempo()
{
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(5, 0);
  oled.setTextSize(2);
  oled.println("--TIEMPO--");
  oled.setTextSize(1);
  oled.println("");
  oled.println("1.  15 seg");
  oled.println("2.  30 seg");
  oled.println("3.  45 seg");
  oled.println("4.  1 min");
  oled.display();
}

void  menupri()
{
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.setTextSize(2);
  oled.println("---MENU---");
  oled.println("");
  oled.setTextSize(1);
  oled.println("1.  Intensidad");
  oled.println("2.  Tiempo");
  oled.display();

}
void  aviso()
{
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
void loop() {

  menuINT();
  
}
