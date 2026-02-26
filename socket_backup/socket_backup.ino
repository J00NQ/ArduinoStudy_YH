#include <WiFi.h>
#include <WiFiMulti.h>
#include <SocketIoClient.h> // Gil Maimon 버전 라이브러리 권장
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 4

WiFiMulti WiFiMulti;
SocketIoClient webSocket;
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "5층";
const char* password = "48864886";
const char *serverIp = "192.168.0.54";
const int port = 5000;

float temp, humi;
unsigned long previousMillis = 0;
const long interval = 10000;
const int led = 2;
int ledstate = 0;
String webString = "";
char ch[52] = {0};

// 연결 성공 시 호출
void handleconnect(const char * payload, size_t length){
  Serial.println("Connected to websocket\n");
  webSocket.emit("join_dev", "{\"room\": \"DEV\"}");
  delay(1000);
}

// LED 제어 이벤트 수신
void handleled(const char * payload, size_t length){
  // 서버에서 'on' 또는 'off' 데이터를 보낼 때 처리
  ledstate = !ledstate;
  digitalWrite(led, ledstate);
  Serial.print("LED state changed to: "); 
  Serial.println(ledstate);
}

void gettemphumi();

void gettemphumi(){
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp)){
    Serial.println("Failed to read dht sensor");
    return;
  }
}

void handleevents(){
  gettemphumi();
  webString="{\"temperature\": \"" + String(temp) + "\", \"humidity\": \"" + String(humi) + "\"}";
  webString.toCharArray(ch, webString.length()+1);
  Serial.println(ch);
  webSocket.emit("events", ch);
  yield();
}

void setup(){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  delay(10);
  dht.begin();

  WiFiMulti.addAP(ssid, password);
  while (WiFiMulti.run() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());

  // 이벤트 핸들러 등록
  webSocket.on("connect", handleconnect);
  webSocket.on("led_control", handleled);

  webSocket.begin(serverIp, port, "/socket.io/?EIO=4");
}

void loop(){
  webSocket.loop();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    handleevents();
  }
}