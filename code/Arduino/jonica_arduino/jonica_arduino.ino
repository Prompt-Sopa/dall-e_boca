// -------------------------------------------------- Include
#include <Servo.h>

// -------------------------------------------------- Declaraciones
#define MODE_PREFIX           "mode"
#define SERVO_MOTOR_1_PREFIX  "sm1p"
#define SERVO_MOTOR_2_PREFIX  "sm2p"

// TODO: Para que quede más ordenado, poner todo esto en un archivo .h separado
#define SERVO_MOTOR_1 9 // Servo motor clasificador

// -------------------------------------------------- Constantes
enum modesOfOperation{
  STOP = 0,
  RUN,
  PREPARE, 
};

// -------------------------------------------------- Classes
Servo servoMotor1;  

// -------------------------------------------------- Variables Globales
int pos = 0;    // Variable to store the servo position

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
        break;
      case RUN:
        // TODO: Code
        break;
      case PREPARE:
        // TODO: Code
        break;
      default:
        break;
    }
  }
  
  // TODO: Otra forma de hacerlo es tipo con un switch cases, pero es masomenos lo mismo
  servoMotorComm(servoMotor1, msg, SERVO_MOTOR_1_PREFIX);
  // TODO: Agregar resto de servos. La RPi hace todo y manda la posicion unicamente
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

// -------------------------------------------------- Main`
void setup() {
  servoMotor1.attach(SERVO_MOTOR_1); 
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
}
