// Pin PWM al que está conectado el transistor
const int pwmPin = 3;
int speed = 0;

void setup() {
  // Configurar el pin PWM como salida
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if(Serial.available() > 0){
    String inputString = Serial.readStringUntil('\n');
    
    // Convertir la cadena a un número entero
    int speed = inputString.toInt();

    // Imprimir el valor recibido para depuración
    Serial.print("Velocidad recibida: ");
    Serial.println(speed);

    // Asegurarse de que el valor esté dentro del rango permitido de PWM (0-255)
    speed = constrain(speed, 0, 255);

    // Escribir el valor de velocidad al pin PWM
    analogWrite(pwmPin, speed);
  }
}
