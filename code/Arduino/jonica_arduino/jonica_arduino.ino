// -------------------------------------------------- Include
#include <Servo.h>
#include "SerialComm.h"
#include "ObjectInput.h"
#include "ConveyerBelt.h"
#include "Clasificador.h"
#include "Pinout.h"

// -------------------------------------------------- Declaraciones

// -------------------------------------------------- Constantes

// -------------------------------------------------- Variables Globales

// -------------------------------------------------- Classes
Clasificador clasificador(CLASIFIER_SWITCHES, SERVO_MOTOR_CLASSIFIER, SERVO_MOTOR_RAMP);
ObjectInput objectInput(SERVO_MOTOR_INPUT);
ConveyerBelt conveyerBelt(CC_MOTOR_CONVEYER_BELT);
SerialComm serialComm;

// -------------------------------------------------- Funciones
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
 
  clasificador.setUp();
  objectInput.setUp();
  conveyerBelt.setUp();
  
  // DEBUG
  // pinMode(13, OUTPUT); 

  Serial.begin(9600);
}

void loop() {

  serialComm.serialCommunicationRead();

  switch(serialComm.getMode()){
    case RUN:
      conveyerBelt.motonOn();
      clasificador.moveClassifier(serialComm.getClassifierMotorAngle());
      clasificador.moveRamp(serialComm.getRampMotorAngle());
      objectInput.cycleControl();
      break;

    case STOP: 
      if(objectInput.cycleFinished()){
        conveyerBelt.motorOff();
      } 
      break;

    case PREPARE:
      for(int i = 0; i < MAX_CONTAINERS; i++){
          clasificador.containerState(i);
        }
      if(clasificador.containerDetection()){
        clasificador.serialCommSendContainers();
      } 
      break;
  }
}
