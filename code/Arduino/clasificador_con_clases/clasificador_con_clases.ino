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
#define CONTAINER_DETECTION_DELAY 1000

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

// -------------------------------------------------- Clases
class Clasificador{
  private: 
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

    int containers[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  
  public:
    void setUp(){
      for(int i = 0; i < 8; i++){
        pinMode(CLASIFIER_SWITCHES[i], INPUT);
      }
    }

    void containerState(int n) {
      /* DESCRIPCIÓN 
      GENERICA - TIENE DEBOUNCE
      */
      
      int reading = digitalRead(CLASIFIER_SWITCHES[n]);

      // If the switch changed, due to noise or pressing:
      if (reading != lastSwitchState[n]) {
        // reset the debouncing timer
        lastSwitchDebounceTime[n] = millis();
      }

      if ((millis() - lastSwitchDebounceTime[n]) > DEBOUNCE_DELAY) {
        if (reading != switchState[n]) {
          switchState[n] = reading;
        }
      }

      // save the reading. Next time through the loop, it'll be the lastSwitchState:
      lastSwitchState[n] = reading;
    }

    void containerDetection(){
      /**/
      // Faltaría una especie de reset para el containerNumber
      // Sino se puede usar siempre el siguiente valor al más alto, aunque es más trabajo al pedo
      static long lastContainerDetectionTime;
      static bool containerDetected = false;
      static int containerNumber = 1; 
      bool newContainer = false;

      if(!containerDetected){
        for(int i = 0; i < 8; i++){
          if(switchState[i] != lastSwitchState[i]){
            containerDetected = true;
            lastContainerDetectionTime = millis();
            // Serial.println("Container detected!");
          }
        }
        return;
      }

      if((millis() - lastContainerDetectionTime) > CONTAINER_DETECTION_DELAY){
        containerDetected = false;
        // Serial.println("Container size verification...");

        for(int j = 0; j < 8; j++){
          // Esto funciona solamente si se hacen las cosas bien!!
          // No se pueden poner diversos containers en simultáneo
          if(!containers[j] && switchState[j]){
              containers[j] = containerNumber;
              newContainer = true;
            }
          if(containers[j] && !switchState[j]){
            containers[j] = 0;
          }
          // Serial.print(containers[j]);
          // Serial.print(" ");
        }
        if(newContainer){ \
          containerNumber++; 
        }
        // Serial.println();
      }
      return;
    }

    void printSwitchState(){
      /**/
      for(int i = 0; i < 8; i++){
        Serial.print(switchState[i]);
        Serial.print(" ");
      }
      Serial.println("");
    }

};

// -------------------------------------------------- Variables Globales

Clasificador clasificador;

// -------------------------------------------------- Funciones

// -------------------------------------------------- Interrupciones

// -------------------------------------------------- Main
void setup() {
  // put your setup code here, to run once:
  clasificador.setUp();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 8; i++){
    clasificador.containerState(i);
  }
  clasificador.containerDetection();
  // clasificador.printSwitchState();
}
