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
  
  Serial.println("");
  Serial.print("Temperatura: ");
  Serial.print( imu.temp() );
  Serial.println(); 
  
 
  //-- Scaled and calibrated output:
  // Accel
  Serial.println("");
  Serial.println("Acelerometro");
  Serial.print("x: ");
  Serial.print( imu.ax() );
  Serial.println( " " );
   Serial.print("y: ");
  Serial.print( imu.ay() );
  Serial.println( " " );
   Serial.print("z: ");
  Serial.print( imu.az() );
  Serial.println( " " );
  delay(2000);

  Serial.println("");
  Serial.println("Giroscopio");
  Serial.print("x: ");
  Serial.print( imu.gx() );
  Serial.println( " " );
   Serial.print("y: ");
  Serial.print( imu.gy() );
  Serial.println( " " );
   Serial.print("z: ");
  Serial.print( imu.gz() );
  Serial.println( " " );
  delay(2000);

  
  
 
  
  // Temp
  
}
