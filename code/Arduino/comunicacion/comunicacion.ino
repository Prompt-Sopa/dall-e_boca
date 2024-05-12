int testArray[] = {1, 2, 3, 4, 5, 6, 7, 8};

void sendArray(int* array){
  // Sacar el largo del array de forma genérica con sizeof supongo
  for(int i = 0; i < 8; i++){
      Serial.print(testArray[i]);
      // delay(100);
    }
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sendArray(testArray);
}
