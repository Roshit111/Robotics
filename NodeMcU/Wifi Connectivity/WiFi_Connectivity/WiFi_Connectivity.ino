#include <ESP8266WiFi.h>

#define BAUD_RATE 115200
#define WIFI_Led D4

#define WIFI_SSID "Roshit"
#define WIFI_PASS "19091809"

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(WIFI_Led, OUTPUT);
  WiFiSetup();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.printf("\r\n [WiFi] : Connection Lost !");
    WiFiSetup();
  }
}

void WiFiSetup() {
  Serial.printf("\r\n [WiFi] : Connecting ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(WIFI_Led, LOW);
    delay(500);
    digitalWrite(WIFI_Led, HIGH);

    attempts++;
    if (attempts > 20) {
      Serial.printf("\n [WiFi] : Failed to connect to WiFi. Check credentials or network.");
      return;
    }
  }

  digitalWrite(WIFI_Led, LOW);
  Serial.printf("\n [WiFi] : Successfully Connected");
  Serial.printf("\n [WiFi] : Network Name -> %s", WIFI_SSID);
  Serial.printf("\n [WiFi] : IP Address   -> %s", WiFi.localIP().toString().c_str());
  Serial.println("");
}