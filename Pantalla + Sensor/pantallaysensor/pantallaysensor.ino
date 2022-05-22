#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h> 
#include <Keypad.h> 
#include <basicMPU6050.h> 
#include <EEPROM.h>
#define ANCHO 128 
#define ALTO 64    
#define OLED_RESET 4  
#define sw1 A0
#define buzzer_pin 4

Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET); 


int address;

// Create instance
basicMPU6050<> sensor;

void setup() {
  // Set registers - Always required
  sensor.setup();

  // Initial calibration of gyro
  sensor.setBias();

  Wire.begin();        
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  oled.clearDisplay();
  oled.display();

  // Start console
  Serial.begin(38400);
}

void loop() { 
  // Update gyro calibration 
  /*imu.updateBias();
  
  Serial.println("****************");
  Serial.println( "" );
  Serial.print("Temperatura: ");
  Serial.print( imu.temp() );
  Serial.println(); 
  Serial.println( "----------------" );
   
  EEPROM.update(address,imu.temp());
  Serial.print(address);
  Serial.print("\t");
  Serial.println(imu.temp());
  delay(2000);*/
 
  //-- Scaled and calibrated output:
  // Accel

    oled.clearDisplay();
    oled.setTextColor(WHITE);  
    oled.setCursor(0, 0);    
    oled.setTextSize(1);    
    oled.println("Acelerometro: ");
    oled.print("x: ");
    oled.println(sensor.ax());
    oled.print("y: ");
    oled.println(sensor.ay());
    oled.print("z: ");
    oled.println(sensor.az());
    oled.println("Giroscopio: ");
    oled.print("x: ");
    oled.println(sensor.gx());
    oled.print("y: ");
    oled.println(sensor.gy());
    oled.print("z: ");
    oled.println(sensor.gz());
    oled.display();


    /*

  Serial.println("");
  
  Serial.println ("Acelerometro:"); 

  
  Serial.print("x: ");  
  Serial.print( sensor.ax() ); Serial.print("\t"); 

   Serial.print("y: ");
  Serial.print( sensor.ay() ); Serial.print("\t"); 
  Serial.print("\t"); 

   Serial.print("z: "); 
  Serial.print( sensor.az() );Serial.println("\t"); 
  
  Serial.println( "----------------" );
  
  
  Serial.println ("Giroscopio:"); 
  
  Serial.print("x: ");  
  Serial.print( sensor.gx() ); Serial.print("\t"); 

  Serial.print("y: ");
  Serial.print( sensor.gy() ); Serial.print("\t"); 
  Serial.print("\t"); 

  Serial.print("z: "); 
  Serial.print( sensor.gz() );Serial.println("\t"); 
  
  Serial.println( "----------------" );
  Serial.println("");

  delay(300);

*/
  
  
 
  
  // Temp
  
}







        
        
          





  
  
