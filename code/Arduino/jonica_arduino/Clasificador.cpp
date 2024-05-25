// -------------------------------------------------- Includes
#include "Clasificador.h"

// -------------------------------------------------- Methods
Clasificador::Clasificador(int switchPin[], int classifierMotorPin, int rampMotorPin){
  this->classifierSwitches = switchPin;
  this->classifierMotorPin = classifierMotorPin;
  this->rampMotorPin = rampMotorPin;
}

void Clasificador::setUp(){
  for(int i = 0; i < MAX_CONTAINERS; i++){
    pinMode(this->classifierSwitches[i], INPUT);
  }
  this->servoMotorClassifier.attach(this->classifierMotorPin);
  this->servoMotorRamp.attach(this->rampMotorPin);

  this->servoMotorClassifier.write(CLASSIFIER_MOTOR_INITIAL_POS);
  this->servoMotorRamp.write(RAMP_MOTOR_INITIAL_POS);
}

int* Clasificador::getContainers(){
  return this->containers; 
}

void Clasificador::containerState(int n){
  /* Control del estado del switch con anti-debounce */      
  
  int reading = digitalRead(this->classifierSwitches[n]);

  // If the switch changed, due to noise or pressing:
  if (reading != this->lastSwitchState[n]) {
    // reset the debouncing timer
    this->lastSwitchDebounceTime[n] = millis();
  }

  if ((millis() - this->lastSwitchDebounceTime[n]) > DEBOUNCE_DELAY) {
    if (reading != this->switchState[n]) {
      this->switchState[n] = reading;
    }
  }

  // save the reading. Next time through the loop, it'll be the lastSwitchState:
  this->lastSwitchState[n] = reading;
}

bool Clasificador::containerDetection(){
  /* Al detectar un contenedor, espera un cierto tiempo. 
  Todos los switch que se cirren, correspondientes al tamaño del contenedor, en ese tiempo tendrán el mismo ID */
  
  static long lastContainerDetectionTime;
  static bool containerDetected = false;
  static int containerNumber = 1; 
  bool newContainer = false, removedContainer = false;

  if(!containerDetected){
    for(int i = 0; i < MAX_CONTAINERS; i++){
      if(this->switchState[i] != this->lastSwitchState[i]){
        containerDetected = true;
        lastContainerDetectionTime = millis();
      }
    }
    // Se deja un tiempo para la detección de containers
    return false;
  }

  if((millis() - lastContainerDetectionTime) > CONTAINER_DETECTION_DELAY){
    containerDetected = false;

    for(int j = 0; j < MAX_CONTAINERS; j++){
      // TODO: Esto funciona solamente si se hacen las cosas bien!!
      // No se pueden poner diversos containers en simultáneo
      if(!containers[j] && this->switchState[j]){
          containers[j] = containerNumber;
          newContainer = true;
        }
      if(containers[j] && !this->switchState[j]){
        containers[j] = 0;
        removedContainer = true;
      }
    }
    if(newContainer){
      containerNumber++; 
    }
    if(removedContainer){
      containerNumber--;
    }
    return true;
  }

  return false;
}

void Clasificador::serialCommSendContainers(){
  /*DESCRIPTION*/
  for(int i = 0; i < MAX_CONTAINERS; i++){
    Serial.print(this->containers[i]);
    Serial.println();
  }
}

void Clasificador::printSwitchState(){
  /*DESCRIPTION*/
  for(int i = 0; i < MAX_CONTAINERS; i++){
    Serial.print(this->switchState[i]);
    Serial.print(",");
  }
  Serial.println();
}

void Clasificador::moveClassifier(int angle){
  // DEBUG
  // Serial.print("Move classifier. Angle: ");
  // Serial.println(angle);
  this->servoMotorClassifier.write(angle);
}

void Clasificador::moveRamp(int angle){
  // DEBUG
  // Serial.print("Move ramp. Angle: ");
  // Serial.println(angle);
  this->servoMotorRamp.write(angle);
}