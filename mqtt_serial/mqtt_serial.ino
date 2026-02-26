/******************************************************************************
MQTT_Switch_Example.ino
Example for controlling a light using an MQTT switch
by: Alex Wende, SparkFun Electronics

This sketch connects the ESP32 to a MQTT broker and subcribes to the topic
room/light. When the button is pressed, the client will toggle between
publishing "on" and "off".
설정 파일 열기
sudo nano /etc/mosquitto/mosquitto.conf

맨 아래 추가
listener 1883
allow_anonymous true

재시작
sudo systemctl restart mosquitto
******************************************************************************/

#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid =  "5층";   // name of your WiFi network
const char *password =  "48864886"; // password of the WiFi network

const byte SWITCH_PIN = 0;           // Pin to control the light with
const char *ID = "Example_Switch";  // Name of our device, must be unique
const char *TOPIC = "room/light";  // Topic to subcribe to

IPAddress broker(192,168,0,54); // IP address of your MQTT broker eg. 192.168.1.50
WiFiClient wclient;

PubSubClient client(wclient); // Setup MQTT client
bool state=0;

// Connect to WiFi network
void setup_wifi() {
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // Connect to network

  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Reconnect to client
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(ID)) {
      Serial.println("connected");
      Serial.print("Publishing to: ");
      Serial.println(TOPIC);
      Serial.println('\n');

    } else {
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud
  pinMode(SWITCH_PIN,INPUT);  // Configure SWITCH_Pin as an input
  digitalWrite(SWITCH_PIN,HIGH);  // enable pull-up resistor (active low)
  delay(100);
  setup_wifi(); // Connect to network
  client.setServer(broker, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // --- 추가된 부분: 시리얼 모니터 입력 처리 ---
  if (Serial.available() > 0) {
    // 줄바꿈 문자(\n)가 나올 때까지 문자열을 읽음
    String input = Serial.readStringUntil('\n');
    input.trim(); // 앞뒤 공백 및 줄바꿈 기호 제거

    if (input.length() > 0) {
      client.publish(TOPIC, input.c_str()); // MQTT 전송 (c_str()로 변환 필요)
      Serial.print("Serial Input Published: ");
      Serial.println(input);
    }
  }

  // --- 기존 코드: 버튼(스위치) 처리 ---
  if (digitalRead(SWITCH_PIN) == 0) {
    state = !state;
    if (state == 1) {
      client.publish(TOPIC, "on");
      Serial.println((String)TOPIC + " => on");
    } else {
      client.publish(TOPIC, "off");
      Serial.println((String)TOPIC + " => off");
    }

    while (digitalRead(SWITCH_PIN) == 0) {
      yield();
      delay(20);
    }
  }
}