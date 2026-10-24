
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "SafeNest 360"
#define BLYNK_AUTH_TOKEN "YOUR_DEVICE_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

const int WATER_PIN = 34;
const int FIRE_BUTTON_PIN = 25;
const int ELECTRIC_BUTTON_PIN = 26;

BlynkTimer timer;

void sendAlerts() {
  // Water sensor: use the digital output (DO) if your
  // specific module provides one.
  int waterAlert = (digitalRead(WATER_PIN) == LOW) ? 1 : 0;

  // Buttons simulate fire and electrical alerts.
  int fireAlert = (digitalRead(FIRE_BUTTON_PIN) == LOW) ? 1 : 0;
  int electricAlert = (digitalRead(ELECTRIC_BUTTON_PIN) == LOW) ? 1 : 0;

  Blynk.virtualWrite(V0, waterAlert);
  Blynk.virtualWrite(V1, fireAlert);
  Blynk.virtualWrite(V2, electricAlert);
}

void setup() {
  Serial.begin(115200);

  pinMode(WATER_PIN, INPUT);
  pinMode(FIRE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(ELECTRIC_BUTTON_PIN, INPUT_PULLUP);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sendAlerts);
}

void loop() {
  Blynk.run();
  timer.run();
}
