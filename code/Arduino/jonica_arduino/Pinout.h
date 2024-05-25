#ifndef PINOUT_H
#define PINOUT_H

/*
[ ----- PINOUT (in order) ----- ]
---------------------------------
D0    |   Serial Rx 
D1    |   Serial Tx
D2    |   Containers Switch A
D3    |   Containers Switch B   
D4    |   Containers Switch C
D5    |   Containers Switch D
D6    |   Containers Switch E
D7    |   Containers Switch F
D8    |   Motor CC (cinta transportadora)
D9    |   Servo Motor 1 (clasificador)
D10   |   Servo Motor 2 (separador)
D11   |   Servo Motor 3 (sistema de entrada)
D12   |   Containers Switch G   
D13   |   Containers Switch H
A0    |
A1    |
A2    |
A3    |
A4    |
A5    |
*/

// TODO: Actualizar esto después
#define CC_MOTOR_CONVEYER_BELT  3
#define SERVO_MOTOR_CLASSIFIER  9 // Servo motor clasificador
#define SERVO_MOTOR_RAMP        10
#define SERVO_MOTOR_INPUT       11

#define CLASSIFIER_SWITCH_A     2
#define CLASSIFIER_SWITCH_B     4
#define CLASSIFIER_SWITCH_C     5
#define CLASSIFIER_SWITCH_D     6
#define CLASSIFIER_SWITCH_E     7
#define CLASSIFIER_SWITCH_F     8
#define CLASSIFIER_SWITCH_G     12
#define CLASSIFIER_SWITCH_H     13

const int CLASIFIER_SWITCHES[8] = {
  CLASSIFIER_SWITCH_A,
  CLASSIFIER_SWITCH_B,
  CLASSIFIER_SWITCH_C,
  CLASSIFIER_SWITCH_D,
  CLASSIFIER_SWITCH_E,
  CLASSIFIER_SWITCH_F,
  CLASSIFIER_SWITCH_G,
  CLASSIFIER_SWITCH_H,
};

#endif