#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid      = "5층";
const char* password  = "48864886";

WiFiClient client;
const char* host = "192.168.0.180";
unsigned int port = 9999;
char wbuf[20];

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (!client.connect(host, port)){
    Serial.println("connection failed");
    return;
  }
}

void loop(){
  int n = 0;
  if (Serial.available() > 0){
    n = Serial.readBytes(wbuf, 20);
    wbuf[n] = '\0';
    Serial.print(wbuf);
    client.print(wbuf);
    Serial.println("send ok");
  }
  delay(1000);
}