/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-ultrasonic-sensor
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char *ssid = "5층"; 
const char *password = "48864886";
// const char *mqtt_server = "192.168.0.54"; // 라즈베리 파이 IP
const char *MQTT_ID = "mymqtt1";          // TODO: 학생마다 고유하게 변경
const char *TOPIC   = "device/01/mymqtt1";   // 서버에서 나타나는 내 아이디입니다.

IPAddress broker(192, 168, 0, 54);              // TODO: 라즈베리파이 IP로 변경
const int MQTT_PORT = 1883;

#define TRIG_PIN 23 // ESP32 pin GPIO23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 22 // ESP32 pin GPIO22 connected to Ultrasonic Sensor's ECHO pin

#define DHTPIN 4       // DHT11 연결 핀
#define DHTTYPE DHT11  // 센서 종류

unsigned long previousMillis = 0;
const long interval = 2000;   // 2초마다 측정 및 전송

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

float duration_us, distance_cm;
float last_temp = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect(MQTT_ID)) {
      Serial.println("connected");
      Serial.print("Publishing to: ");
      Serial.println(TOPIC);
      Serial.println();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

float measureDistance() {
  // TODO: 1단계에서 작성한 코드를 여기에 복사
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH, 30000); 

  // calculate the distance
  distance_cm = duration_us * 0.0343 / 2;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
  return distance_cm;  // TODO: 실제 측정값으로 교체
}

void setup() {
  Serial.begin(115200);
  // configure the trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  // configure the echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
  dht.begin();
  delay(100);
  setup_wifi();
  client.setServer(broker, MQTT_PORT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    } 
    if (t > 30 || abs(t - last_temp) >= 1.0){
      float distance = measureDistance();

      if (distance > 0) {
        String payload = String(distance) + ", " + String(t);
        client.publish(TOPIC, payload.c_str());
        
        Serial.print("Published Data: ");
        Serial.println(payload);

        last_temp = t;
      }
    }
  }
}
