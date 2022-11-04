const int buzzer = 1;
const int botaoS = 5;
const int botaoP = 4;
const int LDR = 7;
const int led1 = 47;
const int led2 = 45;
const int led3 = 35;
const int led4 = 37;
int valores[100];
int Vatual = 0;
void som(int value){
  tone(buzzer, 100*value, 500);
}
void luz(int value){
    if(value == 15){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
  } else if(value == 14){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
  } else if(value == 13){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
  } else if(value == 12){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
  } else if(value == 11){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
  } else if(value == 10){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
  } else if(value == 9){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
  } else if(value == 8){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
  } else if(value == 7){
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
  } else if(value == 6){
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
  } else if(value == 5){
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
  } else if(value == 4){
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
  } else if(value == 3){
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
  } else if(value == 2){
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);
  } else if(value == 1){
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
  } else if(value == 0){
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
  }
}
void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(botaoS, INPUT_PULLUP);
  pinMode(botaoP, INPUT_PULLUP);
  for(int i = 0; i <100; i++){
    valores[i] = -1;
  }
}
void loop() {
  if(!digitalRead(botaoS)){
    int a = map(analogRead(LDR), 32, 4063, 0, 15);
    Serial.println(a);
    valores[Vatual] = a;
    som(a);
    luz(a);
    Vatual += 1;
    delay(1000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
  if(!digitalRead(botaoP)){
    //Serial.println("entrou");
    for(int i = 0; i < Vatual; i++){
      som(valores[i]);
      luz(valores[i]);
      valores[i] = -1;
      delay(1000);
    }
  }
}