#define SERVO_MOTOR_CLASIFIER "m1"
#define SERVO_MOTOR_RAMP      "m2"

int testArray[] = {1, 2, 3, 4, 5, 6, 7, 8};

void sendArray(int* array){
  // Sacar el largo del array de forma genérica con sizeof supongo
  for(int i = 0; i < 8; i++){
      Serial.print(testArray[i]);
      Serial.println();
      // delay(100);
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // sendArray(testArray);
  if (Serial.available() > 0) { 
    String mensaje = Serial.readStringUntil('\n'); // Lee el mensaje hasta que se encuentra un salto de línea
    // String mensaje = "m1p60"; // Lee el mensaje hasta que se encuentra un salto de línea
    Serial.print("ARDUINO: Mensaje recibido: ");
    Serial.println(mensaje); 
    if (mensaje.startsWith("m1p")) { // Verifica si el mensaje comienza con "m1p"
      int valor = mensaje.substring(3).toInt(); 
      Serial.print("Valor recibido: ");
      Serial.println(valor); 
    }
  }
}
