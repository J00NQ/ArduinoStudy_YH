int pushButton = 2;
int ledPin = 12;


void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(pushButton);
  if (buttonState == HIGH){
    Serial.println("LED ON");
    digitalWrite(ledPin, HIGH);
  } else {
    Serial.println("LED OFF");
    digitalWrite(ledPin, LOW);
  }
  delay(50);  
}