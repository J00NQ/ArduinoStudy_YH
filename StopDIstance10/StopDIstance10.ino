const int motorA1 = 6;
const int motorA2 = 7;
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance > 10){
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
  } else if (distance <= 10){
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
  }  
  delay(100);
}