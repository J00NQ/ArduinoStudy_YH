const int ledPin = 11;
const int sensorPin = A0;
void setup() {
  pinMode(ledPin, OUTPUT); // LED 핀을 출력으로 설정
  Serial.begin(9600);


}

void loop() {
  int sensorValue = analogRead(sensorPin); //  (0-1023 범위)
  int brightness = map(sensorValue, 0, 1023, 0, 255); // LED 밝기를 0-1023 범위에서 0-255 범위로 변환
  analogWrite(ledPin, brightness); // LED 밝기 설정
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(voltage);
  delay(1000);
}
