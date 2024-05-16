#ifndef CLASIFICADOR_H
#define CLASIFICADOR_H

// -------------------------------------------------- Includes
#include <Arduino.h>

// -------------------------------------------------- Constantes
#define DEBOUNCE_DELAY 50
#define CONTAINER_DETECTION_DELAY 1000
#define MAX_CONTAINERS 8

// -------------------------------------------------- Class definition
class Clasificador{
  private: 
    int *clasifierSwitches;

    int switchState[MAX_CONTAINERS];
    int lastSwitchState[MAX_CONTAINERS] = {0, 0, 0, 0, 0, 0, 0, 0};
    long lastSwitchDebounceTime[MAX_CONTAINERS] = {0, 0, 0, 0, 0, 0, 0, 0};

    int containers[MAX_CONTAINERS] = {0, 0, 0, 0, 0, 0, 0, 0};
  public:
    Clasificador(int switchPin[]);
    void setUp();
    int* getContainers();

    // TODO: Falta una especie de reset para cada vez que se setean los containers, o que guarde el valor anterior, no sé
    void containerState(int n);
    bool containerDetection();
    void serialCommSendContainers();
    void printSwitchState();
};

#endif