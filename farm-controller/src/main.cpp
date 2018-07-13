#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

#include <devices_io.hpp>

#include "config.hpp"
#include "init.hpp"
#include "web_server.hpp"


void setup() {
  init_serial();
  //present_self_to_serial();
  //web_server_init();
  init_devices_io();
  //Serial.printf("Connecting to %s\n", WIFI_SSID);
  //WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //while (WiFi.status() != WL_CONNECTED) {
  //  delay(500);
  //  Serial.print(".");
  //}
  //Serial.println("");
  //Serial.println("WiFi connected");
  //Serial.println(WiFi.localIP());
  WiFi.disconnect();
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
}

//ADC_MODE(ADC_VCC);

void loop() {
  //digitalWrite(D0, HIGH);
  delay(1990);
  //digitalWrite(D0, LOW);
  Serial.printf("Water level: %f cm\n", read_water_level());
  //web_server.handleClient();
}
