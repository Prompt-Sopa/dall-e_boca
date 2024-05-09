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

// -------------------------------------------------- Includes
#include "Clasificador.h"

// -------------------------------------------------- Constantes

// -------------------------------------------------- Declaraciones
// Para la comucación UART se puede utilizar D0 y D1, o conectar por USB
// D0 - RX
// D1 - TX

#define CLASIFIER_SWITCH_A 2
#define CLASIFIER_SWITCH_B 3
#define CLASIFIER_SWITCH_C 4
#define CLASIFIER_SWITCH_D 5
#define CLASIFIER_SWITCH_E 6
#define CLASIFIER_SWITCH_F 7
#define CLASIFIER_SWITCH_G 8
#define CLASIFIER_SWITCH_H 9

// -------------------------------------------------- Clases

// -------------------------------------------------- Variables Globales

const int CLASIFIER_SWITCHES[8] = {
  CLASIFIER_SWITCH_A,
  CLASIFIER_SWITCH_B,
  CLASIFIER_SWITCH_C,
  CLASIFIER_SWITCH_D,
  CLASIFIER_SWITCH_E,
  CLASIFIER_SWITCH_F,
  CLASIFIER_SWITCH_G,
  CLASIFIER_SWITCH_H,
};

Clasificador clasificador(CLASIFIER_SWITCHES);

// -------------------------------------------------- Funciones

// -------------------------------------------------- Interrupciones

// -------------------------------------------------- Main
void setup() {
  // put your setup code here, to run once:
  // clasificador.setUp();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 8; i++){
    clasificador.containerState(i);
  }
  clasificador.containerDetection();
  // clasificador.printSwitchState();
}
