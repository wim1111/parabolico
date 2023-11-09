// CODIGO HECHO POR WIMI :] PROYECTO TIRO PARABOLICO USFX FAC. TEC. FIS-210.
// codigo que permite calcular la velocidad haciendo uso de 2 sensores fotodiodos
#include <LiquidCrystal_I2C.h> //esta libreria controla el modulo ic2 y se la debe descargar de internet 
                               //https://www.electroallweb.com/index.php/2019/12/13/modulo-i2c-para-pantallas-lcd/

#include <Wire.h> //funciona sin esta libreria, pero en la documentacion de arduino recominedan incluir esta libreria nativa
LiquidCrystal_I2C lcd(0x27,16,2); // lapantalla lcd usada funciona con 27.c `ppp
                                  // si duda de cual colocar recomiendo esta pagina que contiene codigo muy util:
                                  //https://catedu.github.io/programa-arduino-mediante-codigo/3-entradas-y-salidas/31-lcd/313-escaneo.html

//definimos tipos de variables.
int Sentrada1 = 2; // Entrada de señal 1 pin(2) cable cafe
int Sentrada2 = 3; // entrada de señal 2  pin(3)cable naranja
int sensor1;       // aqui se almacenara el valor de 0 o 1 del senso 1
int sensor2;       // aqui se almacenara el valor de 0 o 1 del senso 2

unsigned long  tiempo1;   //tiempo de inicial. 
unsigned long  tiempo2;   //tiempo final.
unsigned long  tiempot;   //tiempo total. en us (micro-segundos) tiempot=tiempo2-tiempo1.

float velocidad;          // alamcenara el valor de la velocidad.
float distancia = 165000; // la distancia de sensor a sensor = 16.5 cm pero lo convertimos a (micro-metros)
                          // esto debido a que al momento de convertir el tiempo de us a s no genera un valor correcto
                          // esto se lo soluciona convirtiendo los cm a um. A si (u)m con (u)s se simplifica y solo queda m/s
      
 void setup() {
                            
  Serial.begin(9600); // inicializamos el monitor serie. (consola)
  Serial.println("CARGANDO EL SYSTEMA ESPERE 8S");
  lcd.init();                    //se inicia el modulo ic2 y la pantalla lcd 
  lcd.backlight();              //activamos la luz de fondo.
  lcd.setCursor(0, 0);         // 1era Posicion, 1era Fila.
  lcd.print("HOLA SOY WIMI :]"); //mensaje en la fila de arriba.
  lcd.setCursor(0, 1);       // 1era Posicion, 2da Fila.
  lcd.print(" I.A del sistema");  // mensaje en la fila de abajo.

  delay(3000);                  //se detiene el programa por 3s.
  lcd.clear();
  
    lcd.init();                    //se inicia el modulo ic2 y la pantalla lcd 
  lcd.backlight();              //activamos la luz de fondo.
  lcd.setCursor(0, 0);         // 1era Posicion, 1era Fila.
  lcd.print("    PROYECTO"); //mensaje en la fila de arriba.
  lcd.setCursor(0, 1);       // 1era Posicion, 2da Fila.
  lcd.print(" TIRO PARABOLICO");  // mensaje en la fila de abajo.

  delay(4000);                  //se detiene el programa por 3s.
  lcd.clear();

  lcd.setCursor(0, 0);         //solo un mensaje para que se vea COOL :).
  lcd.print("EL SYSTEMA ESTA");
  lcd.setCursor(0, 1);
  lcd.print("CARGANDO........");

  delay (2000);               //tiempo de espera del programa de 2s.
  lcd.clear();                //limpiara la pantalla.

  lcd.setCursor(0, 0);        //posicion 0 fila 0.
  lcd.print("DISPARE EL ");
  lcd.setCursor(0, 1);        //posicion 0 fila 1.
  lcd.print("    PROYECTIL :]");  //solo es otro mensaje.

  delay (3000);                //detener el programa por 4s.
  

  pinMode(Sentrada1, INPUT);  //pin en modo entrada de señal 1.
  pinMode(Sentrada2, INPUT);  //pin en modo entrada de señal 2.

  Serial.println("200 OK :] ");                 //mensaje guiño a REDES :).
  Serial.println("EN ESPERA DEL DISPARO....");
  

}

void loop() {
  sensor1 = digitalRead(Sentrada1); //tomara la lectura digital de 0 - 1 del primer  sensor1.
  sensor2 = digitalRead(Sentrada2); //tomara la lectura digital de 0 - 1 del segundo sensor2.
  
  while (sensor1 == 0) {
    // esta en espera del proyectil pase por el  sensor 1.
    sensor1 = digitalRead(Sentrada1);  //esto tomara el valor del sensor en reposo es igual a 0 y cuando pase el proyectil por el sensor 1
                                       //el cual rompera el bucle y continuara con el algoritmo.
  }

  tiempo1 = micros(); //esto captura el tiempo de ejecucion en este punto y esta medido en micro-segundos, para mayor presicion.

  while (sensor2 == 0 ) {
    //esta en espera del proyectil que pase por el sensor 2.
    sensor2 = digitalRead(Sentrada2);    //esto tomara el valor del sensor en reposo es igual a 0 y cuando pase el proyectil por el sensor 1
                                         //el cual rompera el bucle y continuara con el algoritmo.
  }

  tiempo2 = micros(); //capturara el tiempo de ejecucion en este otro punto y esta medido en micro-segundos, para mayor presicion.
  
  tiempot = tiempo2 - tiempo1;  //calculo del tiempo transcurrido entre la activacion del sensor 1 al sensor2. 
  velocidad = (distancia / tiempot); //calculo de la velocidad.
 
//se imprimiran las variables en el monitor serie

  Serial.println("*****");
  Serial.print("timepo1 = ");            
  Serial.println(tiempo1);
  Serial.print("tiempo2 = ");
  Serial.println(tiempo2);
  Serial.print("tiempo-total = ");
  Serial.println(tiempot); 
  Serial.print("distancia = ");
  Serial.println(distancia);
  Serial.print("V =");
  Serial.print(distancia);
  Serial.print(" um / ");
  Serial.print(tiempot);
  Serial.println(" us");
  Serial.print("v = ");
  Serial.print(velocidad);
  Serial.println(" m/s");
  Serial.println("*****");

    // para limpiar la pantalla no se  puede usar la funcion clear();
    
    lcd.setCursor(0,0);    
    lcd.print("                ");
    lcd.setCursor(0,1);    
    lcd.print("                ");
  
    //imprimir dato del tiempo en us en la parte de arriba.  

    lcd.setCursor(0,0);    
    lcd.print("t = ");
    lcd.setCursor(4,0);
    lcd.print(tiempot);  
    lcd.setCursor(13,0);
    lcd.print("us");
   
    //imprimir dato de la velocidad en la parte de abajo.
    
    lcd.setCursor(0,1);
    lcd.print("v = ");
    lcd.setCursor(4,1);
    lcd.print(velocidad,5);// imprime el valor de la velociad con 5  decimales.
    lcd.setCursor(12,1);
    lcd.print("m/s");
       delay (10);
  
}
