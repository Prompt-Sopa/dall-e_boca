// -------------------------------------------------- Include
#include <Servo.h>
#include "Clasificador.h"
#include "Pinout.h"

// -------------------------------------------------- Declaraciones
#define MODE_PREFIX           "mode"
#define SERVO_MOTOR_1_PREFIX  "sm1p"
#define SERVO_MOTOR_2_PREFIX  "sm2p"

// -------------------------------------------------- Constantes
enum operationModes{
  STOP = 0,
  RUN,
  PREPARE, 
};

// -------------------------------------------------- Classes
Servo servoMotor1;  

// -------------------------------------------------- Variables Globales
int pos = 0;    // Variable to store the servo position

const int CLASIFIER_SWITCHES[8] = {
  CLASIFIER_SWITCH_A,
  CLASIFIER_SWITCH_B,
  CLASIFIER_SWITCH_C,
  CLASIFIER_SWITCH_D,
  CLASIFIER_SWITCH_E,
  CLASIFIER_SWITCH_F,
  CLASIFIER_SWITCH_G,
  CLASIFIER_SWITCH_H,
};

Clasificador clasificador(CLASIFIER_SWITCHES);

int mode = STOP;

// -------------------------------------------------- Funciones
void servoMotorComm(Servo servo, String msg, char* prefix){
  /* Compares the serial message prefix and moves the servo motor to the corresponding position */
  
  if (msg.startsWith(prefix)) { 
    int valor = msg.substring(strlen(prefix)).toInt(); 
    servo.write(valor);
  }
}

void serialMsgProcessing(String msg){
  // TODO: Capaz es más rápido solo un char, a tener en cuenta
  if(msg.startsWith(MODE_PREFIX)){
    switch(msg.substring(strlen(MODE_PREFIX)).toInt()){
      case STOP:
        // TODO: Code
        // Detiene cinta transportadora
        mode = STOP;
        break;
      case RUN:
        // TODO: Code
        // Activa cinta transportadora
        // Activa los servos
        mode = RUN;
        break;
      case PREPARE:
        // TODO: Code
        // Activa deteccion de contenedores
        mode = PREPARE;
        break;
      default:
        break;
    }
    return;
  }
  
  if(mode == RUN){
    // TODO: Otra forma de hacerlo es tipo con un switch cases, pero es masomenos lo mismo
    servoMotorComm(servoMotor1, msg, SERVO_MOTOR_1_PREFIX);
    // TODO: Agregar resto de servos. La RPi hace todo y manda la posicion unicamente
    return;
  }
}

void ledBlink(){
  for(int i=0; i<10; i++){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
}

// -------------------------------------------------- Interrupciones

// -------------------------------------------------- Main
void setup() {
  servoMotor1.attach(SERVO_MOTOR_1); 
  clasificador.setUp();
  
  // TODO: Solo test, quitar
  pinMode(13, OUTPUT); 
  
  Serial.begin(9600);
}

void loop() {
  
  // TODO: Faltan las variables que indican en que estado del sistema nos encontramos. Hacerlo con un enum?
  if (Serial.available() > 0) { 
    String serialMessage = Serial.readStringUntil('\n');
    serialMsgProcessing(serialMessage);
  }

  if(mode == PREPARE){
    for(int i = 0; i < MAX_CONTAINERS; i++){
      clasificador.containerState(i);
    }
    clasificador.containerDetection();
    // TODO: Si hay un cambio en los contenedor, enviar el array por serial comm
  } 
}
