#ifndef CONVEYER_BELT_H
#define CONVEYER_BELT_H

// -------------------------------------------------- Includes
#include <Arduino.h>

// -------------------------------------------------- Constantes
// TODO: Estaría bueno poder setearlo
#define SPEED 150

// -------------------------------------------------- Class definition
class ConveyerBelt{
  private:
    int motorPin;
  
  public:
    ConveyerBelt(int motorPin);
    void setUp();

    void motonOn(){analogWrite(this->motorPin, SPEED);};
    void motorOff(){analogWrite(this->motorPin, 0);};
};

#endif
