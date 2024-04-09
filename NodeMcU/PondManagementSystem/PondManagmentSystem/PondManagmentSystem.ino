// Required Libraries
#include <Event.h>
#include <Timer.h>
#include <OneWire.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <DallasTemperature.h>


// Variable Declaration
#define BAUD_RATE 115200
#define WIFI_SSID "XXXXXXXX"  // WiFi Name
#define WIFI_PASS "XXXXXXXX"  // WiFi Password

#define CHKey 2499401               // ThingSpeak Channel Id
#define WAPIKey "2L2LMH4ZTW30UP2C"  // ThingSpeak Write Api Key
int TSPH = 1;
int TSLV = 2;
int TSTE = 3;
int TSSA = 4;

// Pin Declaration
#define Salinity A0
#define Turbine D0       // Turbine Pin For Temperature Controller
#define ONE_WIRE_BUS D1  // Data Pin for Temperature Sensor

// Object Creation
Timer t;
WiFiClient client;
OneWire oneWire(ONE_WIRE_BUS);
SoftwareSerial SoftSerial(2, 3);
DallasTemperature Sensor(&oneWire);
#pragma GCC diagnostic ignored "-Wwrite-strings"

// Variable Declaration
float TempC = 0.0;
float TempF = 0.0;
int SalinityValue = 0;

void setup() {
  Serial.begin(BAUD_RATE);   // Initialize serial communication
  WiFiSetup();               // Connect to WiFi
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  pinMode(Salinity, INPUT);
  pinMode(Turbine, OUTPUT);  // Set Turbine pin as output
}


void loop() {
  WifiCheck();  // Check WiFi connection
  if (WiFi.status() == WL_CONNECTED) {
    Sensors();
  }
}
void Sensors() {
  WaterTemp();      // Read water temperature
  WaterSalinity();  // Read water salinity
}

// Function to check WiFi connection
void WifiCheck() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.printf("\r\n [WiFi] : Connection Lost !");
    WiFiSetup();
  }
}

// Function to connect to WiFi
void WiFiSetup() {
  Serial.printf("\r\n [WiFi] : Connecting ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    attempts++;
    if (attempts > 20) {
      Serial.printf("\n [WiFi] : Failed to connect to WiFi. Check credentials or network.");
      return;
    }
    delay(1000);
  }

  Serial.printf("\n [WiFi] : Successfully Connected");
  Serial.printf("\n [WiFi] : Network Name -> %s", WIFI_SSID);
  Serial.printf("\n [WiFi] : IP Address   -> %s \n", WiFi.localIP().toString().c_str());
}

// Function to send data to ThingSpeak
void sendThingSpeak(int field, float value) {
  ThingSpeak.writeField(CHKey, field, value, WAPIKey);
}

// Function to read water temperature
void WaterTemp() {
  Sensor.requestTemperatures();
  // TempC = Sensor.getTempCByIndex(0);
  TempC = 24;
  // TempF = Sensor.getTempFByIndex(0);
  Serial.printf("\n [ Water ] : Temperature Celsius -> %f", TempC);
  // Serial.printf("\n [ Water ] : Temperature Fahrenheit -> %f", TempF);

  if (TempC < 22)
    digitalWrite(Turbine, HIGH);  // Water Temperature is Low
  else if (TempC >= 22 && TempC <= 27)
    digitalWrite(Turbine, LOW);  // Water Temperature is Normal
  else if (TempC > 27)
    digitalWrite(Turbine, HIGH);  // Water Temperature is High

  delay(1000);
  t.update();
  sendThingSpeak(TSTE, TempC);
}

// Function to read water salinity
void WaterSalinity() {
  // SalinityValue = analogRead(Salinity);
  SalinityValue = 50;
  // SalinityValue = map(SalinityValue, 0, 1023, 0, 100);

  if (SalinityValue >= 50)
    Serial.printf("\n [ Water ] : Salinity -> %f is High", SalinityValue);  // Use %f for floating-point values
  if (SalinityValue < 50)
    Serial.printf("\n [ Water ] : Salinity -> %f is Low", SalinityValue);  // Use %f for floating-point values

  delay(1000);
  t.update();
  sendThingSpeak(TSSA, SalinityValue);
}