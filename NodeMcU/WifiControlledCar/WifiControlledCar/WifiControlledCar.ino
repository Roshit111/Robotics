// Blynk Device Information
#define BLYNK_TEMPLATE_ID "TMPL3gVeLtX-D"
#define BLYNK_TEMPLATE_NAME "Smart Car"
#define BLYNK_AUTH_TOKEN "iOto2gffH27E5yFnFFUf-OjlImGgQEZS"

// Including Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WIFI Information
char wifi_ssid[] = "XXXXXXXX";    // WIFI Name
char wifi_pass[] = "XXXXXXXX";  // WIFI Password

// Pin Configuration
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D4
#define IN4 D3
#define ENB D5
#define BAUDRATE 115200

// Define Directions default values
bool isForward = false, isBackward = false, isLeft = false, isRight = false;

// Define Default speed value
int speed = 0;

// Setup Function
void setup() {
  Serial.begin(BAUDRATE);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  connectToBlynk();
}

// Blynk Connectivity Function
void connectToBlynk() {
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi_ssid, wifi_pass, "blynk.cloud", 80);
  if (Blynk.connected()) {
    Serial.println("Connected to Blynk server.");
  } else {
    Serial.println("Failed to connect to Blynk server!");
  }
}

// Blynk Virtual Pin Handlers
BLYNK_WRITE(V0) {
  speed = param.asInt();
}
BLYNK_WRITE(V1) {
  isForward = param.asInt();
}
BLYNK_WRITE(V2) {
  isBackward = param.asInt();
}
BLYNK_WRITE(V3) {
  isLeft = param.asInt();
}
BLYNK_WRITE(V4) {
  isRight = param.asInt();
}

// Smart Car Function
void smartCar() {
  if (isForward) {
    carMove(IN1, IN2, IN3, IN4);
    Serial.println("Forward");
  } else if (isBackward) {
    carMove(IN2, IN1, IN4, IN3);
    Serial.println("Backward");
  } else if (isLeft) {
    carMove(IN2, IN1, IN3, IN4);
    Serial.println("Left");
  } else if (isRight) {
    carMove(IN1, IN2, IN4, IN3);
    Serial.println("Right");
  } else {
    carStop();
    Serial.println("Stop");
  }
}

// Loop Function
void loop() {
  Blynk.run();
  smartCar();
}

// Car Movement Functions
void carMove(int in1, int in2, int in3, int in4) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}