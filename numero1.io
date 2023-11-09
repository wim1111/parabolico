/* codigo echo por wimi (^u^)/
 * usfx
 * proyecto tiro parabolico
 * control de servo mediante control remoto y potenciometro
 */

#include <IRremote.hpp>           //libreria IR actualizada 10/23
int IRpin = 9;                    // señal del IR 
int codigo;                       //almacenara los valores codificados en decimal del control remoto
int paso;                         // esto cuenta los pasos de 5 para los bucles

#include <Servo.h>              //libreria para  controlar el servo
Servo servo1;                    //variable para controlar el servo
int Servopin=6;
int potenciometro_pin=A0;       // entrada de señal del potenciometro
int pot_valor=0;                // almacenara losvalores dados del potenciometro 
int angulo=90;                  //se pondra en angulo de 90 al inicio
int power=4;                    //esto es de suma importancia para apagar el potenciometro
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           // activar del monitor serie
  servo1.attach(Servopin);      //asigamos la señal de salida para el servo
  IrReceiver.begin(IRpin);      // asignamos la señal de entrada para el sensor infra rojo
  pinMode (potenciometro_pin,INPUT);  // tomamos el pin en modo lectura analoga de la señal del potenciometro
  servo1.write(angulo);             //le asignamos el angulo al servo
  pinMode (power,INPUT);        //pin en modo lectura
}

void loop() {
  Serial.print("valor de power=");    //imprime el  vlaor de power
   Serial.println(digitalRead(power));  //iniciamos el pin en modo lectura digital 0-1
   
  while (IrReceiver.decode() == 0) {   // en espera de que se presione algun boton
   if(digitalRead(power)==1){           // condicion para el encendido y apagado del potenciometro; 
  pot_valor= analogRead(potenciometro_pin); //se almacena el valor del potenciometro en la variable pot_valor
  angulo=map(pot_valor,0,1023,0,180);           // hace una conversion donde 0 entrada es = 0 angulo y 1023entrada es =180 grados 
  servo1.write(angulo);                        // asigna el angulo  
  delay(10);
    }
  }
  Serial.println(IrReceiver.decodedIRData.command);   // imprime los valores dados por elcontrol remoto en valores decimal 
codigo=IrReceiver.decodedIRData.command;    //los valores en decimal son almacenados enesta variable 
switch (codigo){                            //esta funcion condicion comparara los valores que tiene con la variable codigo
  case  12:
  servo1.write (0);               // para angulo de 0 grados boton 7
  delay (15);
  break;

   case 13:
  servo1.write (45);          // para angulo de 45 grados boton 8
  delay (15);
  break;

   case 14:
  servo1.write (90);          // para angulo de 90 grados boton 9
  delay (15);
  break;


   case 18: 
  paso = servo1.read();           // para angulo de donde esta  a 180 grados
for (int i=paso; i<181; i++)
{
servo1.write(i);
delay(20);
}
  break;

case 16:
paso = servo1.read ();
for (int i=paso; i>-i; i--)   // para angulo de donde esta  a 0 grados
{
  servo1.write (i);
  delay(20);
}

break;
    
}


  delay(500);
  IrReceiver.resume();   // limpia los datos para que no exista ruido es decir lo lleva a la posicion inicial 0 como valor decimal 

}
