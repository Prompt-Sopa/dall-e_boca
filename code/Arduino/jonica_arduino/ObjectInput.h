#ifndef INPUT_H
#define INPUT_H

// -------------------------------------------------- Includes
#include <Arduino.h>
#include <Servo.h>

// -------------------------------------------------- Constantes
#define FINAL_ANGLE 65
#define CYCLE_FREQUENCY 15000

// -------------------------------------------------- Class definition
class ObjectInput{
  private:
    int motorPin;
    Servo servoMotor;
    long startCycleTime = 0;
  
  public:
    ObjectInput(int motorPin);
    void setUp();

    bool cycleFinished();
    void pushNewObject();
    void cycleControl();

    int getFrequency(){ return CYCLE_FREQUENCY; };
    int getstartCycleTime(){ return startCycleTime; };
};

#endif