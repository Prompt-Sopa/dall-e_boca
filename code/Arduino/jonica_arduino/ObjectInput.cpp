// -------------------------------------------------- Includes
#include "ObjectInput.h"

ObjectInput::ObjectInput(int motorPin){
  this->motorPin = motorPin;
}

void ObjectInput::setUp(){
  this->servoMotor.attach(this->motorPin);
  servoMotor.write(0);
}

void ObjectInput::pushNewObject(){
  // TODO: Sería mejor hacerlo con interrupciones o algo así, porque tilda todo
  int angle = 0;
  bool finished = false;
  long prevMillis = millis();
  const int movDelay = 15, fallDelay = 500;

  // Move forward
  while(!finished){
    if(this->servoMotor.read() >= MOTOR_FINAL_POS){
      finished = true;
    }
    else{
      if(millis() - prevMillis > movDelay){
        prevMillis = millis();
        angle++;
        this->servoMotor.write(angle);
      }
    }
  }
  
  // Wait a couple of milliseconds
  finished = false;
  while(!finished){
    if(millis() - prevMillis > fallDelay){
      prevMillis = millis();
      finished = true;
    }
  }

  // Move backwards to origin
  finished = false;
  while(!finished){
    if(this->servoMotor.read() <= MOTOR_INITIAL_POS){
      finished = true;
    }
    else{
      if(millis() - prevMillis > movDelay){
        prevMillis = millis();
        angle--;
        this->servoMotor.write(angle);
      }
    }
  }
}

bool ObjectInput::cycleFinished(){
  return millis() - this->startCycleTime > CYCLE_FREQUENCY;
}

void ObjectInput::cycleControl(){
  if(this->cycleFinished()){
    this->startCycleTime = millis();
    this->pushNewObject();
  }
}
