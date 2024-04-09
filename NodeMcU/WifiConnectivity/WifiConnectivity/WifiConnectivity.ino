#include <ESP8266WiFi.h>

#define BAUD_RATE 115200
#define WIFI_Led D4

#define WIFI_SSID "XXXXXXXX"        // WiFi Name
#define WIFI_PASS "XXXXXXXX"        // WiFi Password

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(WIFI_Led, OUTPUT);
  WiFiSetup();
}

void loop() {
  WifiCheck();
}

void WifiCheck() {
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
    Serial.print(".");
    digitalWrite(WIFI_Led, HIGH);
    delay(500);
    digitalWrite(WIFI_Led, LOW);
    delay(500);

    attempts++;
    if (attempts > 20) {
      Serial.printf("\n [WiFi] : Failed to connect to WiFi. Check credentials or network.");
      return;
    }
  }

  Serial.printf("\n [WiFi] : Successfully Connected");
  Serial.printf("\n [WiFi] : Network Name -> %s", WIFI_SSID);
  Serial.printf("\n [WiFi] : IP Address   -> %s \n", WiFi.localIP().toString().c_str());
}