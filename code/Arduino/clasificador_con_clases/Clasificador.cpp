// -------------------------------------------------- Includes
#include "Clasificador.h"

// -------------------------------------------------- Methods
Clasificador::Clasificador(int switchPin[]){
  this->clasifierSwitches = switchPin;
}

void Clasificador::setUp(){
  for(int i = 0; i < 8; i++){
    pinMode(clasifierSwitches[i], INPUT);
  }
}

void Clasificador::containerState(int n){
  /* DESCRIPCIÓN 
      GENERICA - TIENE DEBOUNCE
  */
      
      int reading = digitalRead(clasifierSwitches[n]);

      // If the switch changed, due to noise or pressing:
      if (reading != lastSwitchState[n]) {
        // reset the debouncing timer
        lastSwitchDebounceTime[n] = millis();
      }

      if ((millis() - lastSwitchDebounceTime[n]) > DEBOUNCE_DELAY) {
        if (reading != switchState[n]) {
          switchState[n] = reading;
        }
      }

      // save the reading. Next time through the loop, it'll be the lastSwitchState:
      lastSwitchState[n] = reading;
}

void Clasificador::containerDetection(){
 /**/
  // Faltaría una especie de reset para el containerNumber
  // Sino se puede usar siempre el siguiente valor al más alto, aunque es más trabajo al pedo
  static long lastContainerDetectionTime;
  static bool containerDetected = false;
  static int containerNumber = 1; 
  bool newContainer = false;

  if(!containerDetected){
    for(int i = 0; i < 8; i++){
      if(switchState[i] != lastSwitchState[i]){
        containerDetected = true;
        lastContainerDetectionTime = millis();
        // Serial.println("Container detected!");
      }
    }
    return;
  }

  if((millis() - lastContainerDetectionTime) > CONTAINER_DETECTION_DELAY){
    containerDetected = false;
    // Serial.println("Container size verification...");

    for(int j = 0; j < 8; j++){
      // Esto funciona solamente si se hacen las cosas bien!!
      // No se pueden poner diversos containers en simultáneo
      if(!containers[j] && switchState[j]){
          containers[j] = containerNumber;
          newContainer = true;
        }
      if(containers[j] && !switchState[j]){
        containers[j] = 0;
      }
      // Serial.print(containers[j]);
      // Serial.print(" ");
    }
    if(newContainer){ \
      containerNumber++; 
    }
    // Serial.println();
  }
  return;
}

void Clasificador::printSwitchState(){
  /**/
  for(int i = 0; i < 8; i++){
    Serial.print(switchState[i]);
    Serial.print(" ");
  }
  Serial.println("");
}