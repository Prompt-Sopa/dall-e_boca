// -------------------------------------------------- Include
#include <Servo.h>
#include "SerialComm.h"
#include "ObjectInput.h"
#include "ConveyerBelt.h"
#include "Clasificador.h"
#include "Pinout.h"

// -------------------------------------------------- Declaraciones
#define MODE_PREFIX           "mode"
#define SERVO_MOTOR_1_PREFIX  "sm1p"
#define SERVO_MOTOR_2_PREFIX  "sm2p"

#define CONVEYER_BELT_SPEED   150

// -------------------------------------------------- Constantes
// enum operationModes{
//   STOP = 0,
//   RUN,
//   PREPARE, 
// };

// -------------------------------------------------- Variables Globales
const int CLASIFIER_SWITCHES[8] = {
  CLASSIFIER_SWITCH_A,
  CLASSIFIER_SWITCH_B,
  CLASSIFIER_SWITCH_C,
  CLASSIFIER_SWITCH_D,
  CLASSIFIER_SWITCH_E,
  CLASSIFIER_SWITCH_F,
  CLASSIFIER_SWITCH_G,
  CLASSIFIER_SWITCH_H,
};

// -------------------------------------------------- Classes
Clasificador clasificador(CLASIFIER_SWITCHES, SERVO_MOTOR_CLASSIFIER);
ObjectInput objectInput(SERVO_MOTOR_INPUT);
ConveyerBelt conveyerBelt(CC_MOTOR_CONVEYER_BELT);
SerialComm serialComm;

// -------------------------------------------------- Funciones
// Esta debería ser una clase aparte para la comunicación, o funciones al menos
void servoMotorComm(Servo servo, String msg, char* prefix){
  /* Compares the serial message prefix and moves the servo motor to the corresponding position */
  
  if(msg.startsWith(prefix)) { 
    int valor = msg.substring(strlen(prefix)).toInt(); 
    servo.write(valor);
  }
}

// void serialMsgProcessing(String msg){
  // TODO: Capaz es más rápido solo un char, a tener en cuenta
  // if(mode == RUN){
  //   // TODO: Otra forma de hacerlo es tipo con un switch cases, pero es masomenos lo mismo
  //   servoMotorComm(servoMotor1, msg, SERVO_MOTOR_1_PREFIX);
  //   // TODO: Agregar resto de servos. La RPi hace todo y manda la posicion unicamente
  //   return;
  // }
// }

void ledBlink(){
  for(int i=0; i<10; i++){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
}

// -------------------------------------------------- Interrupciones

// -------------------------------------------------- Main
void setup() {
 
  // clasificador.setUp();
  objectInput.setUp();
  conveyerBelt.setUp();
  
  // TODO: Solo test, quitar
  // pinMode(13, OUTPUT); 

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) { 
    String serialMessage = Serial.readStringUntil('\n');
    // DEBUG
    Serial.print("Serial Comm: ");
    Serial.println(serialMessage);
    serialComm.serialMsgProcessing(serialMessage);
  }

  switch(serialComm.getMode()){
    case RUN:
      conveyerBelt.motonOn();
      objectInput.cycleControl();
      break;

    case STOP: 
      if(objectInput.cycleFinished()){
        conveyerBelt.motonOff();
      } 
      break;
  }

  // if(mode == PREPARE){
  //   for(int i = 0; i < MAX_CONTAINERS; i++){
  //     clasificador.containerState(i);
  //   }
  //   if(clasificador.containerDetection()){
  //     clasificador.serialCommSendContainers();
  //   }
  // }
}
