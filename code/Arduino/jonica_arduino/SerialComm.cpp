// -------------------------------------------------- Includes
#include "SerialComm.h"

void SerialComm::serialMsgProcessing(String msg){
   if(msg.startsWith(MODE_PREFIX)){
    // TODO: Faltaría agregar una verificación de modo
    this->mode = msg.substring(strlen(MODE_PREFIX)).toInt();
    this->printMode();
    return this->mode; 
  }
}

void SerialComm::printMode(){
  switch(this->mode){
    case STOP:
      Serial.println("Mode: STOP");
      break;
    case RUN:
      Serial.println("Mode: RUN");
      break;
    case PREPARE:
      Serial.println("Mode: PREPARE");
      break;
    default:
      Serial.println("MODE UNKOWN!");
      break;
  }
}