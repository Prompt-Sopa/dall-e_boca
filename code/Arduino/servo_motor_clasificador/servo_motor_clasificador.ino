// -------------------------------------------------- Notas
/*
  - Comunicación UART con RPi
    - Enviar lo sensado de los contenedores
    - Recibir la posición del servo
  - Mover Servo Motor
  - Detección de contenedores
    - Función genérica de antirebote para un botón
    - Tiempo entre primera detección para guardar las otras y tirar dato
  X - Actualización de los contenedores de según sean 1, 2, 3, etc. Aunque esto lo hace la RPi aahahaha

*/

// -------------------------------------------------- Include
#include <Servo.h>

// -------------------------------------------------- Constantes

// -------------------------------------------------- Declaraciones

// -------------------------------------------------- Classes
Servo myservo;  // create servo object to control a servo

// -------------------------------------------------- Variables Globales
int pos = 0;    // variable to store the servo position

// -------------------------------------------------- Funciones

// -------------------------------------------------- Interrupciones

// -------------------------------------------------- Main
void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // put your main code here, to run repeatedly:
  // for (pos = 0; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(1);                       // waits 15 ms for the servo to reach the position
  // }
  // for (pos = 120; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(1);                       // waits 15 ms for the servo to reach the position
  // }
  myservo.write(0);
  delay(2000);
  myservo.write(180);
  delay(2000);
}
