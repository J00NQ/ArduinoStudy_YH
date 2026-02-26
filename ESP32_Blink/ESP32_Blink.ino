// ESP32 기본 Blink 예제

const int ledPin = 2;   // ESP32 내장 LED (보통 GPIO 2)

void setup() {
  pinMode(ledPin, OUTPUT);   // LED 핀을 출력 모드로 설정
}

void loop() {
  digitalWrite(ledPin, HIGH);  // LED 켜기
  delay(1000);                 // 1초 대기
  
  digitalWrite(ledPin, LOW);   // LED 끄기
  delay(1000);                 // 1초 대기
}