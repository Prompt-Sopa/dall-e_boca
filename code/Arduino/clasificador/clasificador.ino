// -------------------------------------------------- Notas
/*
  - Comunicación UART con RPi
    - Enviar lo sensado de los contenedores
    - Recibir la posición del servo
  - Mover Servo Motor
  - Detección de contenedores
    - Función genérica de antirebote para un botón
    - Tiempo entre primera detección para guardar las otras y tirar dato
  X - Actualización de los contenedores de según sean 1, 2, 3, etc. Aunque esto lo hace la RPi aahahaha

*/

// -------------------------------------------------- Constantes
#define DEBOUNCE_DELAY 50

// -------------------------------------------------- Declaraciones
// Para la comucación UART se puede utilizar D0 y D1, o conectar por USB
// D0 - RX
// D1 - TX

#define CLASIFIER_SWITCH_A 2
#define CLASIFIER_SWITCH_B 3
#define CLASIFIER_SWITCH_C 4
#define CLASIFIER_SWITCH_D 5
#define CLASIFIER_SWITCH_E 6
#define CLASIFIER_SWITCH_F 7
#define CLASIFIER_SWITCH_G 8
#define CLASIFIER_SWITCH_H 9

// -------------------------------------------------- Variables Globales
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

int switchState[8];
int lastSwitchState[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
long lastSwitchDebounceTime[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// -------------------------------------------------- Funciones
void button_state(int buttonPin, int* buttonState, int* lastButtonState, long* lastDebounceTime) {
  /* DESCRIPCIÓN 
  GENERICA - TIENE DEBOUNCE
  */
  
  int reading = digitalRead(buttonPin);

  // If the switch changed, due to noise or pressing:
  if (reading != *lastButtonState) {
    // reset the debouncing timer
    *lastDebounceTime = millis();
  }

  if ((millis() - *lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != *buttonState) {
      *buttonState = reading;
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  *lastButtonState = reading;
}

void print_switch_state(){
  /**/
  for(int i = 0; i++; i < 8){
    Serial.print(switchState[i]);
    Serial.print(" ");
  }
  Serial.println("");
}

void deteccionContenedores(){
  /* DESCRIPCIÓN */

}

// -------------------------------------------------- Interrupciones

// -------------------------------------------------- Main
void setup() {
  
  for(int i = 0; i < 8; i++){
    pinMode(CLASIFIER_SWITCHES[i], INPUT);
  }

}

void loop() {
  
  for(int i = 0; i < 8; i++){
    button_state(CLASIFIER_SWITCHES[i], &switchState[i], &lastSwitchState[i], &lastSwitchDebounceTime[i]);
  }
  print_switch_state();

}
