#include <basicMPU6050.h> 
#include <EEPROM.h>

int address;

// Create instance
basicMPU6050<> imu;

void setup() {
  // Set registers - Always required
  imu.setup();

  // Initial calibration of gyro
  imu.setBias();

  // Start console
  Serial.begin(38400);
}

void loop() { 
  // Update gyro calibration 
  imu.updateBias();
  
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
  delay(2000);
 
  //-- Scaled and calibrated output:
  // Accel

  /*
  Serial.println("");
  
  Serial.println ("Acelerometro:"); 
  
  Serial.print("x: ");  
  Serial.print( imu.ax() ); Serial.print("\t"); 

   Serial.print("y: ");
  Serial.print( imu.ay() ); Serial.print("\t"); 
  Serial.print("\t"); 

   Serial.print("z: "); 
  Serial.print( imu.az() );Serial.println("\t"); 
  
  Serial.println( "----------------" );
  
  
  Serial.println ("Giroscopio:"); 
  
  Serial.print("x: ");  
  Serial.print( imu.gx() ); Serial.print("\t"); 

  Serial.print("y: ");
  Serial.print( imu.gy() ); Serial.print("\t"); 
  Serial.print("\t"); 

  Serial.print("z: "); 
  Serial.print( imu.gz() );Serial.println("\t"); 
  
  Serial.println( "----------------" );
  Serial.println("");

  delay(300);


  
  
 */
  
  // Temp
  
}
