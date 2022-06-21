#include <EEPROM.h>
#include <Wire.h>     
#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h> 

#define ANCHO 128    
#define ALTO 64 
#define OLED_RESET 4 

Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);    

int address; //direccion en la eeprom
int limite=5; //Cantidad de direcciones a utilizar
int ran = 0;
int val = 0;
void setup () {
  Wire.begin();         // inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializa pantalla con direccion 0x3C
  oled.clearDisplay();
  oled.display();
  Serial.begin(9600);
  Serial.print ("Tamano EEPROM:");
  Serial.println(EEPROM.length());//ArduinoUno: 1kb EEPROM storage
  delay (2000);
}

void loop ()
{

  oled.clearDisplay();
  oled.setTextColor(WHITE);   // establece color al unico disponible (pantalla monocromo)
  oled.setCursor(0, 0);     // ubica cursor en inicio de coordenadas 0,0
  oled.setTextSize(1);      // establece tamano de texto en 1
  oled.print("Tamano EEPROM: "); 
  oled.println (EEPROM.length());
  oled.display();
  delay (2000);
  for (address=0; address< limite; address++)
  {
    ran=random(0,10); 
    EEPROM.update(address,ran); //Guarda val en la direccion address
    oled.print(address);
    oled.clearDisplay();
    oled.setTextColor(WHITE);   // establece color al unico disponible (pantalla monocromo)
    oled.setCursor(0, 0);     // ubica cursor en inicio de coordenadas 0,0
    oled.setTextSize(1);      // establece tamano de texto en 1
    oled.print("Guardando: "); 
    oled.println (ran);
    oled.display();
    delay(1000);
    
  }
  Serial.println("Escritura terminada");
  Serial.println("-------------------");
  delay(1000);
  oled.setTextColor(WHITE);   // establece color al unico disponible (pantalla monocromo)
  oled.setCursor(0, 10);     // ubica cursor en inicio de coordenadas 0,0
  oled.setTextSize(1);      // establece tamano de texto en 1
  oled.print("Escritura terminada"); 
  oled.display();
  delay(1000);
  
  //////////////////////////////////////////
  Serial.println("Inicio de lectura");
  delay(5000);
  for (address=0; address< limite; address++)
  {
    val=EEPROM.read(address); 
    oled.clearDisplay();
    oled.setTextColor(WHITE);   // establece color al unico disponible (pantalla monocromo)
    oled.setCursor(0, 0);     // ubica cursor en inicio de coordenadas 0,0
    oled.setTextSize(1);      // establece tamano de texto en 1
    oled.print("Direccion: "); 
    oled.println (address);
    oled.print("Valor: "); 
    oled.println (val);
    oled.display();
    delay(760);
  }
  Serial.println("Lectura terminada");
  Serial.println("-------------------");
  

}
