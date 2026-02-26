#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char WIFI_SSID[] = "5층";         // CHANGE IT
const char WIFI_PASSWORD[] = "48864886"; // CHANGE IT
String HOST_NAME   = "http://192.168.0.54:5000"; // CHANGE IT
String PATH_NAME   = "/api/sensor";      // CHANGE IT
String serverURL = (HOST_NAME + PATH_NAME);

//String PATH_NAME   = "/products/arduino.php";      // CHANGE IT
// String queryString = "temperature=26&humidity=70";

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("WiFi 연결 중");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi 연결 완료! IP: ");
  Serial.println(WiFi.localIP());

  // HTTPClient http;

  // http.begin(HOST_NAME + PATH_NAME);
  // http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // int httpCode = http.POST(queryString);

  // // httpCode will be negative on error
  // if (httpCode > 0) {
  //   // file found at server
  //   if (httpCode == HTTP_CODE_OK) {
  //     String payload = http.getString();
  //     Serial.println(payload);
  //   } else {
  //     // HTTP header has been send and Server response header has been handled
  //     Serial.printf("[HTTP] POST... code: %d\n", httpCode);
  //   }
  // } else {
  //   Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
  // }
  // http.end();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("센서 읽기 실패!");
    delay(2000);
    return;
  }
  Serial.print("온도: ");
  Serial.print(temperature);
  Serial.print(" / 습도: ");
  Serial.println(humidity);
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");
    char jsonData[100];
    snprintf(jsonData, sizeof(jsonData), "{\"temperature\":%.2f,\"humidity\":%.2f}", temperature, humidity);

    int httpCode = http.POST(jsonData);
    if (httpCode > 0) {
      String response = http.getString();
      Serial.println("서버 응답: " + response);
    } else {
      Serial.println("전송 실패! 코드: " + String(httpCode));
      Serial.println(serverURL);
    }
    http.end();
  }
  delay(5000);
}
