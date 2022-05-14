#include <basicMPU6050.h> 

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
  
 
  //-- Scaled and calibrated output:
  // Accel
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


  
  
 
  
  // Temp
  
}
