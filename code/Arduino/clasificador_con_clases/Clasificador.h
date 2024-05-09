#ifndef CLASIFICADOR_H
#define CLASIFICADOR_H

// -------------------------------------------------- Includes
#include <Arduino.h>

// -------------------------------------------------- Constantes
#define DEBOUNCE_DELAY 50
#define CONTAINER_DETECTION_DELAY 1000

// -------------------------------------------------- Class definition
class Clasificador{
  private: 
    int *clasifierSwitches;

    int switchState[8];
    int lastSwitchState[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    long lastSwitchDebounceTime[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    int containers[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  
  public:
    Clasificador(int switchPin[]);
    void setUp();

    void containerState(int n);
    void containerDetection();
    void printSwitchState();
};

#endif