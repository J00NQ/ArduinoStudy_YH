const int motorA1 = 6;
const int motorA2 = 7;
const int trigPin = 9;
const int echoPin = 10;

// defines variables
long duration;
int distance;
int lastSpeed;
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
  int targetSpeed;
  if (distance > 30) {
    targetSpeed = 200;
  } else if (distance > 5 && distance <= 30) {
    targetSpeed = map(distance, 5, 30, 110, 200); 
  } else {
    targetSpeed = 0;
  }

  // 멈춰있다가 다시 움직여야 할 때 (킥 스타트)
  if (lastSpeed == 0 && targetSpeed > 0) {
    analogWrite(motorA1, 255); // 순간적으로 풀 파워
    delay(50);                 // 아주 짧게 툭 쳐줌
  }

  analogWrite(motorA1, targetSpeed);
  lastSpeed = targetSpeed; // 현재 속도 저장
  
  delay(50);
}