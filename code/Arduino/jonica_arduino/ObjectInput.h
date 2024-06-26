#ifndef INPUT_H
#define INPUT_H

// -------------------------------------------------- Includes
#include <Arduino.h>
#include <Servo.h>

// -------------------------------------------------- Constantes
#define MOTOR_INITIAL_POS 65
#define MOTOR_FINAL_POS 0
#define CYCLE_FREQUENCY 5000

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