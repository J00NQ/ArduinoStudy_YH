const int ledPin = 13;  // the number of the LED pin
const int buttonPin = 2;

int buttonState = 0;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop(){
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH){
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

}