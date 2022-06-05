#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

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
char sub_aux;
int seleccion_duraccion(char sub_aux);

int sw;
#define sw1 7

int intensidad = 0;
int duracion = 0;

float val_intensidad = 0;


// AREA DE SUBPROGRAMAS PARA MEL MENU


void menu_inicial(){

  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(32,0);
  oled.setTextSize(1);
  oled.println("Menu inicial");
  oled.println("\nModos de manejo: ");
  oled.println("\n1.  Bluetooth");  
  oled.println("\n2.  Manual");
  oled.display();
}

void menu_apagado(){

  oled.clearDisplay();
  oled.setTextColor(WHITE);   
  oled.setCursor(0, 30);     
  oled.setTextSize(1);      
  oled.print("Sistema: Apagado");
  oled.display();
}

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
  oled.setCursor(0,56);
  oled.print("A.  Volver");
  oled.display();   
}

void menu_manual(){
  
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(10,0);
  oled.setTextSize(1);
  oled.println("-- Manejo manual --");
  oled.setTextSize(1);
  oled.setCursor(0,14);
  oled.print("1.  Intensidad");
  oled.setCursor(0,24);
  oled.print("2.  Duracion");
  oled.setCursor(0,34);
  oled.print("3.  Parametros");
  oled.setCursor(0,44);
  oled.print("B.  Simular");
  oled.setCursor(0,54);
  oled.print("A.  Volver");
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

void volver(){
  tecla='X'; 
}

void volver_sub(){
  aux='X';
}



void setup() { 
  
  Serial.begin(9600);
  Wire.begin();         // inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializa pantalla con direccion 0x3C
  oled.clearDisplay();
  oled.display();

}
 
void loop() {

// LECTURAS Y ESCRITURAS DE PUERTOS

  sw = digitalRead(sw1);
  
  if(sw==1){

    menu_inicial();
    tecla = teclado.getKey();

//  @ MENU MANEJO BLUETOOTH @  //////
   
    while(tecla=='1'){

       menu_bt();
       aux = teclado.getKey();
       
       if(aux=='A'){
        volver();
       }
    }

//  @ MENU MANEJO MANUAL @  //////


    while(tecla=='2'){

       menu_manual();
       aux = teclado.getKey();
        
        
        
 ///// ZONA DE SUBMENUS DE MANEJO MANUAL ////////       
        
        
        while(aux=='1'){

          menu_intensidad();
          sub_aux = teclado.getKey();

          switch(sub_aux){

              case '1' : intensidad = 5; val_intensidad = 2; break;
              case '2' : intensidad = 4; val_intensidad = 3.5; break;
              case '3' : intensidad = 3; val_intensidad = 5; break;
              case '4' : intensidad = 1; val_intensidad = 7; break;
              case 'A' : volver_sub(); break;
          }
        
      }
      
      while(aux=='2'){
           
          menu_duracion();
          sub_aux = teclado.getKey();

          switch(sub_aux){

              case '1' : duracion = 15; break;
              case '2' : duracion = 30; break;
              case '3' : duracion = 45; break;
              case '4' : duracion = 60; break;
              case 'A' : volver_sub(); break;
          }      
      }

      while(aux=='3'){

          muestra_parametros(val_intensidad, duracion);
          sub_aux = teclado.getKey();

          if(sub_aux=='A'){

            volver_sub();
          } 
      }
      
      while(aux=='B'){

        // falta subprograma para inicializacion del sismo
          sub_aux = teclado.getKey();
          if(sub_aux=='A'){
  
              volver_sub();

          }
      }
      
      if(aux=='A'){

        volver();
      }       
    } 
  }
  
   else{
    
    menu_apagado();
    
  }
}
