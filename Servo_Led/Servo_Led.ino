#include <Servo.h>

Servo myservo;  
const int analogPin = A0;
const int servoPin = 9;
const int ledRed = 12;
const int ledGreen = 11;

int pos = 0;    

void setup() {
  myservo.attach(servoPin); 
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void loop() {
  int analogVal = analogRead(analogPin);
  int mVal = map(analogVal, 0, 1023, 0, 180);
  pos = mVal;
  myservo.write(pos);              
  if (pos >= 30 || pos <= 150){     // 정상범위(30~150)이면 초록색 led 점등
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  } else {                          // 정상범위 벗어날 경우 빨간색 led 점등
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
  }
  delay(15);                  
}