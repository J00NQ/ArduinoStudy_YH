#include <WiFi.h>          // ESP8266용 대신 ESP32용 WiFi 라이브러리 사용
#include <WebServer.h>     // ESP8266WebServer 대신 WebServer 사용
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 4           // ESP32의 GPIO 4번 핀 사용
const char* ssid = "5층";
const char* password = "48864886";

// ESP32용 웹 서버 클래스 선언
WebServer server(80);

DHT dht(DHTPIN, DHTTYPE);

float temp, humi;
String webString = "";
unsigned long previousMillis = 0;
const long interval = 2000;

void gettemphumi();

void handleevents(){
  gettemphumi();
  webString = "{\"temperature\": \"" + String(temp) + "\", \"humidity\": \"" + String(humi) + "\"}";

  Serial.println(webString);
  server.send(200, "text/plain", webString);
}

void setup(){
  Serial.begin(115200);
  delay(10);
  dht.begin();

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/events", handleevents);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  server.handleClient();
}

void gettemphumi(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    humi = dht.readHumidity();
    temp = dht.readTemperature();
    
    if (isnan(humi) || isnan(temp)){
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}