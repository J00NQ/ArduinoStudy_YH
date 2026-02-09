int sensorPin = A0;   // select the input pin for the potentiometer
int ledPin = 12;      // select the pin for the LED
int ledPin2 = 11;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  
  sensorValue = analogRead(sensorPin);
  if (sensorValue > 700){
    digitalWrite(ledPin, HIGH);  
    digitalWrite(ledPin2, HIGH);  
  } else if (sensorValue > 350) {
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, HIGH);
  } else {
    digitalWrite(ledPin, LOW);  
    digitalWrite(ledPin2, LOW);  
  }
  delay(300);
  Serial.println(sensorValue);
  // digitalWrite(ledPin, HIGH);
  // delay(sensorValue);
  // digitalWrite(ledPin, LOW);
  // delay(sensorValue);
}
