#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
const int analogPin = A0;
const int servoPin = 9;
const int ledRed = 12;
const int ledGreen = 11;

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void loop() {
  int analogVal = analogRead(analogPin);
  int mVal = map(analogVal, 0, 1023, 0, 180);
  pos = mVal;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  if (pos > 150 || pos < 30){
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
  } else {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }
  delay(15);                       // waits 15ms for the servo to reach the position
}