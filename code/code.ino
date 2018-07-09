#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

#include "config.hpp"
#include "init.hpp"

float read_water_level() {
  const static float voltages[] = {0.0, 1.3, 1.53, 1.62, 1.69, 1.74, 1.77, 1.81, 1.84, 1.86, 1.88};
  const static float heights[] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 4.8};
  float in_voltage = 3.3 * analogRead(A0) / 1024;
  Serial.printf("Voltage: %f V\n", in_voltage);
  for (int i = 0; i < 11; i++) {
    if (in_voltage <= voltages[i]) {
      return heights[i];
    }
  }
  return heights[10];
}

void setup() {
  init_serial();
  present_self_to_serial();
  pinMode(D0, OUTPUT);
  Serial.printf("Connecting to %s\n", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
 
void loop() {
  digitalWrite(D0, HIGH);
  delay(1990);
  digitalWrite(D0, LOW); 
  delay(10);
  // Serial.printf("Water level: %f cm\n", read_water_level());
}
 
