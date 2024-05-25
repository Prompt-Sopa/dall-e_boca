#ifndef SERIALCOMM_H
#define SERIALCOMM_H

// -------------------------------------------------- Includes
#include <Arduino.h>

// -------------------------------------------------- Constantes
#define MODE_PREFIX                     "mode"
#define CLASSIFIER_SERVO_MOTOR_PREFIX   "smclass"
#define RAMP_SERVO_MOTOR_PREFIX         "smramp"

enum operationModes{
  STOP = 0,
  RUN,
  PREPARE, 
};

// -------------------------------------------------- Class definition
class SerialComm{
  private:
    int mode = STOP;
    int classifierMotorAngle, rampMotorAngle;

  public:
    void serialCommunicationRead();
    void serialMsgProcessing(String msg);

    int getMode(){return this->mode;};
    int getClassifierMotorAngle() {return this->classifierMotorAngle;};
    int getRampMotorAngle() {return this->rampMotorAngle;};
    void printMode();
};

#endif