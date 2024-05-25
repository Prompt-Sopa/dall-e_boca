// -------------------------------------------------- Includes
#include "SerialComm.h"

void SerialComm::serialMsgProcessing(String msg){
  if(msg.startsWith(MODE_PREFIX)){
    // TODO: Faltaría agregar una verificación de modo
    this->mode = msg.substring(strlen(MODE_PREFIX)).toInt();
    this->printMode();
    return;
  }

  if(msg.startsWith(CLASSIFIER_SERVO_MOTOR_PREFIX)){
    // DEBUG
    // Serial.print("COMM: Classifier motor angle: ");
    // Serial.println(this->classifierMotorAngle);
    this->classifierMotorAngle = msg.substring(strlen(CLASSIFIER_SERVO_MOTOR_PREFIX)).toInt();
    return;
  }

  if(msg.startsWith(RAMP_SERVO_MOTOR_PREFIX)){
    // DEBUG
    // Serial.print("COMM: Ramp motor angle: ");
    // Serial.println(this->rampMotorAngle);
    this->rampMotorAngle = msg.substring(strlen(RAMP_SERVO_MOTOR_PREFIX)).toInt();
    return;
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

void SerialComm::serialCommunicationRead(){
  if (Serial.available() > 0) { 
    String serialMessage = Serial.readStringUntil('\n');
    // DEBUG
    // Serial.print("Serial Comm: ");
    // Serial.println(serialMessage);
    this->serialMsgProcessing(serialMessage);
  }
}