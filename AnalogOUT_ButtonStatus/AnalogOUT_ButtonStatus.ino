const int sensorPin = A0; 
const int ledPin = 9;    
const int buttonPin = 4;
int buttonState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);      
}

void loop() {
  int sensorValue = analogRead(sensorPin); 
  int brightness = map(sensorValue, 0, 1023, 0, 255); 
  int buttonVal = digitalRead(buttonPin);


  if (buttonVal == HIGH){
    if (buttonState == LOW){
      buttonState = HIGH;
    } else {
      buttonState = LOW;
    }
   delay(50); 
  }
  if (buttonState == HIGH) {
    analogWrite(ledPin, brightness);
  } else {
    digitalWrite(ledPin, LOW);
  }
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Brightness: ");
  Serial.println(brightness);

  delay(100); 
}
