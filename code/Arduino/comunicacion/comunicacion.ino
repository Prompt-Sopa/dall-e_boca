#include <Servo.h>

#define SERVO_MOTOR_CLASIFIER "sm1p"
#define SERVO_MOTOR_RAMP      "sm2p"

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int testArray[] = {1, 2, 3, 4, 5, 6, 7, 8};

void serialCommTx(int* array){
  // Sacar el largo del array de forma genérica con sizeof supongo
  for(int i = 0; i < 8; i++){
      Serial.print(testArray[i]);
      Serial.println();
      // delay(100);
    }
}


void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  // serialCommTx(testArray);
  if (Serial.available() > 0) { 
    String mensaje = Serial.readStringUntil('\n'); // Lee el mensaje hasta que se encuentra un salto de línea
    // String mensaje = "sm1p60"; // Lee el mensaje hasta que se encuentra un salto de línea
    
    // Serial.print("ARDUINO: Mensaje recibido: ");
    // Serial.println(mensaje); 
    
    if (mensaje.startsWith("sm1p")) { // Verifica si el mensaje comienza con "m1p"
      int valor = mensaje.substring(4).toInt(); 
      // Serial.print("Valor recibido: ");
      // Serial.println(valor); 
      myservo.write(valor);
    }
  }
}
