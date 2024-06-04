// -------------------------------------------------- Includes
#include "ConveyerBelt.h"

ConveyerBelt::ConveyerBelt(int motorPin){
  this->motorPin = motorPin;
}

void ConveyerBelt::setUp(){
  pinMode(this->motorPin, OUTPUT);
  this->motorOff();
}
