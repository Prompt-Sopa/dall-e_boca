// -------------------------------------------------- Include
#include <Servo.h>
#include "SerialComm.h"
#include "ObjectInput.h"
#include "ConveyerBelt.h"
#include "Classifier.h"
#include "Pinout.h"

// -------------------------------------------------- Declaraciones

// -------------------------------------------------- Constantes

// -------------------------------------------------- Variables Globales

// -------------------------------------------------- Classes
Classifier classifier(CLASIFIER_SWITCHES, SERVO_MOTOR_CLASSIFIER, SERVO_MOTOR_RAMP);
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
 
  classifier.setUp();
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
      // TODO: Sería mejor mover los motores solamente si cambió el ángulo
      classifier.moveClassifier(serialComm.getClassifierMotorAngle());
      classifier.moveRamp(serialComm.getRampMotorAngle());
      objectInput.cycleControl();
      break;

    case STOP: 
      if(objectInput.cycleFinished()){
        conveyerBelt.motorOff();
        Serial.println("cycle_finished");
      } 
      break;

    // case SETUP:
    //   for(int i = 0; i < MAX_CONTAINERS; i++){
    //       classifier.containerState(i);
    //     }
    //   if(classifier.containerDetection()){
    //     classifier.serialCommSendContainers();
    //   } 
    //   break;
  }
}
