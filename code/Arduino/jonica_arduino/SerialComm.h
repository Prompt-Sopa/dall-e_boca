#ifndef SERIALCOMM_H
#define SERIALCOMM_H

// -------------------------------------------------- Includes
#include <Arduino.h>

// -------------------------------------------------- Constantes
#define MODE_PREFIX           "mode"
#define SERVO_MOTOR_1_PREFIX  "sm1p"
#define SERVO_MOTOR_2_PREFIX  "sm2p"

enum operationModes{
  STOP = 0,
  RUN,
  PREPARE, 
};

// -------------------------------------------------- Class definition
class SerialComm{
  private:
    int mode = STOP;
  
  public:
    void serialMsgProcessing(String msg);

    int getMode(){return this->mode;};
    void printMode();
};

#endif