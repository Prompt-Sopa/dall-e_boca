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
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
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
  for(int i=0; i<180; i++){
    myservo.write(i);
    delay(15);
  }
  for(int j=0; j>0; j--){
    myservo.write(j);
    delay(15);
  }

  // delay(1000);
  // myservo.write(30);
  // Serial.write("30");
  // delay(1000);
  // myservo.write(60);
  // Serial.write("60");
  // delay(1000);
  // myservo.write(90);
  // Serial.write("90");
  // delay(1000);
  // myservo.write(120);
  // Serial.write("120");
  // delay(1000);
}
