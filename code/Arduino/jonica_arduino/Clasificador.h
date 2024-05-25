#ifndef CLASIFICADOR_H
#define CLASIFICADOR_H

// -------------------------------------------------- Includes
#include <Arduino.h>
#include <Servo.h>

// -------------------------------------------------- Constantes
#define DEBOUNCE_DELAY 50
#define CONTAINER_DETECTION_DELAY 1000
#define MAX_CONTAINERS 8

#define CLASSIFIER_MOTOR_INITIAL_POS 0
#define RAMP_MOTOR_INITIAL_POS 0

// -------------------------------------------------- Class definition
class Clasificador{
  private: 
    int *classifierSwitches;
    Servo servoMotorClassifier, servoMotorRamp;
    int classifierMotorPin, rampMotorPin;

    int switchState[MAX_CONTAINERS];
    int lastSwitchState[MAX_CONTAINERS] = {0, 0, 0, 0, 0, 0, 0, 0};
    long lastSwitchDebounceTime[MAX_CONTAINERS] = {0, 0, 0, 0, 0, 0, 0, 0};

    int containers[MAX_CONTAINERS] = {0, 0, 0, 0, 0, 0, 0, 0};
  
  public:
    Clasificador(int switchPin[], int classifierMotorPin, int rampMotorPin);
    void setUp();
    int* getContainers();

    void containerState(int n);
    bool containerDetection();
    void serialCommSendContainers();
    void printSwitchState();

    void moveClassifier(int angle);
    void moveRamp(int angle);
};

#endif