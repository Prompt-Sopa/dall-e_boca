// -------------------------------------------------- Includes
#include "Clasificador.h"

// -------------------------------------------------- Methods
Clasificador::Clasificador(int switchPin[]){
  this->clasifierSwitches = switchPin;
}

void Clasificador::setUp(){
  for(int i = 0; i < MAX_CONTAINERS; i++){
    pinMode(this->clasifierSwitches[i], INPUT);
  }
}

int* Clasificador::getContainers(){
  return this->containers; 
}

void Clasificador::containerState(int n){
  /*DESCRIPTION*/      
  int reading = digitalRead(this->clasifierSwitches[n]);

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
  /*DESCRIPTION*/
  // TODO: Faltaría una especie de reset para el containerNumber
  // Sino se puede usar siempre el siguiente valor al más alto, aunque es más trabajo al pedo
  static long lastContainerDetectionTime;
  static bool containerDetected = false;
  static int containerNumber = 1; 
  bool newContainer = false;

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
      }
    }
    if(newContainer){ \
      containerNumber++; 
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
    Serial.print(" ");
  }
  Serial.println("");
}