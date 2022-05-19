#include <Adafruit_GFX.h>  
#include <Adafruit_SSD1306.h> 
#include <Keypad.h> 
#define ANCHO 128 
#define ALTO 64    
#define OLED_RESET 4  
#define sw1 A0
#define buzzer_pin 4

Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET); 

int sw;
int tiempo = 0;
int intensidad= 0;
int temperatura= 30;

const byte FILAS=2;
const byte COLUMNAS=4;
char keys[FILAS][COLUMNAS]= { 
  {'1','2','3','A'},
  {'4','5','6','B'}
};
byte pinesFilas[FILAS]= {10,11};
byte pinesColumnas[COLUMNAS]= {9,8,7,6};
Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

char tecla;
char op='A';
int estadosistema = 0;
int menu=0;


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

void  menu_intensidad(){
  
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
}

void  menu_principal(){

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.setTextSize(2);
  oled.println("---MENU---");
  oled.println("");
  oled.setTextSize(1);
  oled.println("1.  Intensidad");  
  oled.println("");
  oled.println("2.  Tiempo");
  oled.println("");
  oled.display();
}

void  aviso(){
  
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

void sonido_M2(){
  Serial.println("M2");
  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
}

void sonido_M3_5(){
   Serial.println("M3,5");
  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin); 
}

void sonido_M5(){
   Serial.println("M5");
  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
}

void sonido_M7(){
  Serial.println("M7");
  tone(buzzer_pin, 1700);
  delay(200);
  noTone(buzzer_pin);
}


void quinceSegundos() {
  oled.clearDisplay();
  oled.setTextColor(WHITE);  
  oled.setCursor(0, 30);    
  oled.setTextSize(1);    
  oled.print("15 segundos");
  oled.display();
}

void duracion(int tiempo){

  for(int i=0; i<tiempo+1; i++)
  {
    Serial.println(i);
    delay(1000);
     oled.clearDisplay();
  oled.setTextColor(WHITE);  
  oled.setCursor(10, 10);    
  oled.setTextSize(1);    
  oled.println("Tiempo transcurrido");

  oled.setCursor(60, 30);    
  oled.setTextSize(2);    
  oled.print(i);
  oled.display();
  }
}

void resumen(int tiempo, int intensidad, int temperatura){

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(10,0);
  oled.setTextSize(2);
  oled.println("-RESUMEN-");
  
  oled.setCursor(0,20);    
  oled.setTextSize(1);    
  oled.print("Temperatura: ");
  oled.print(temperatura);

  oled.setCursor(0,30);    
  oled.setTextSize(1);    
  oled.print("Intensidad: ");
  oled.print(intensidad);

  oled.setCursor(0,40);    
  oled.setTextSize(1);    
  oled.print("Tiempo: ");
  oled.print(tiempo);
  oled.display();
    
}

void datosAlmacenados(int tiempo, int intensidad){

  if(tiempo>0 && intensidad>0){
    oled.clearDisplay();
  oled.setTextColor(WHITE);  
  oled.setCursor(10, 10);    
  oled.setTextSize(2);    
  oled.println("  Datos   guardados");
  oled.display();
    
  }
  else
  {
    oled.clearDisplay();
  oled.setTextColor(WHITE);  
  oled.setCursor(10, 10);    
  oled.setTextSize(2);    
  oled.println(" Datos NO guardados");
  oled.display();
    
  }
  
}
  

void setup() { 

  Serial.begin(9600);
  Wire.begin();        
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  oled.clearDisplay();
  oled.display();
}
 
void loop() {

  //duracion(15);
  //resumen(tiempo,intensidad,temperatura);
  datosAlmacenados(tiempo, intensidad);
  

  /*
sw = 1; ///ESTO HAY QUE MODIFICAR
tecla= teclado.getKey();
Serial.println(tecla);

    switch(tecla)
     {
        case '1': 
          op='1';
          tone(buzzer_pin, 1700);
          delay(200);
          noTone(buzzer_pin);
         break;
        
        case '2':
         op='2';
         tone(buzzer_pin, 1700);
         delay(200);
         noTone(buzzer_pin);
        break;

        case 'A': 
          op='A';
          tone(buzzer_pin, 1700);
          delay(200);
          noTone(buzzer_pin);
         break;


         case 'B': 
          op='B';
          tone(buzzer_pin, 2700);
          delay(200);
          noTone(buzzer_pin);
         break;
      }

    if (sw==0)
      { 
        off();
      }
  
    else
      {
        
        estadosistema = 1;
        if (menu==0){ 
          switch (op)
            {
            case 'A':
                if (estadosistema==1)
                  {
                     menu_principal();
                  }
              break;
              
            case '1':
              if (estadosistema==1)
              {
                menu_intensidad();  
                menu=1;  
              }
              break;

            case '2':
              if (estadosistema==1)
              {
                 menu_tiempo();
                menu=2; 
              }
              break;
            
            
              break;
        
            default: 
              break;      
          }
        }


        if (menu==1){

          if(tecla){
            switch(op)
              {
                case '1':
                  sonido_M2();
                break;
                
                case '2':
                  sonido_M3_5();
                break;
                
                case '3':
                  sonido_M5();
                break;
                
                case '4':
                  sonido_M7();
                break;
                
                case 'A':
                  menu=0;
                break;
                default: 
                  break;  
              }

        }
        }

        if (menu==2){
            switch(op)
              {
                case '1':
                  quinceSegundos();
                break;
                
                case '2':
                  //30s
                break;
                
                case '3':
                  //45s
                break;
                
                case '4':
                  //1min
                break;    
                case 'A':
                  menu=0;
                break;
                default: 
                  break;  
              }
        }
      }
*/
}





        
        
          





  
  
