const int ledR = 9;
const int ledG = 10;
const int ledB = 11;

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ledR, 255);
  analogWrite(ledG, 0);
  analogWrite(ledB, 0);
  delay(1000);

  // Green
  analogWrite(ledR, 0);
  analogWrite(ledG, 255);
  analogWrite(ledB, 0);
  delay(1000);

  // Blue
  analogWrite(ledR, 0);
  analogWrite(ledG, 0);
  analogWrite(ledB, 255);
  delay(1000);

  // Yellow (R+G)
  analogWrite(ledR, 255);
  analogWrite(ledG, 255);
  analogWrite(ledB, 0);
  delay(1000);

  // Cyan (G+B)
  analogWrite(ledR, 0);
  analogWrite(ledG, 255);
  analogWrite(ledB, 255);
  delay(1000);

  // Magenta (R+B)
  analogWrite(ledR, 255);
  analogWrite(ledG, 0);
  analogWrite(ledB, 255);
  delay(1000);

  // White
  analogWrite(ledR, 255);
  analogWrite(ledG, 255);
  analogWrite(ledB, 255);
  delay(2000);


}
