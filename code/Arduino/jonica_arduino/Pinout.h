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
#define SERVO_MOTOR_1       9 // Servo motor clasificador

#define CLASIFIER_SWITCH_A 2
#define CLASIFIER_SWITCH_B 3
#define CLASIFIER_SWITCH_C 4
#define CLASIFIER_SWITCH_D 5
#define CLASIFIER_SWITCH_E 6
#define CLASIFIER_SWITCH_F 7
#define CLASIFIER_SWITCH_G 8
#define CLASIFIER_SWITCH_H 10

#endif