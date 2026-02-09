int pushButton = 2;
int ledPin = 12;
int ledPin2 = 11;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(pushButton);
  if (buttonState == HIGH){
    Serial.println("LED ON");
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin2, LOW);
  } else {
    Serial.println("LED OFF");
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, HIGH);
  }
  delay(50);  
}