#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

#include <web_server.hpp>
#include <devices_io.hpp>
#include <farm_controller.hpp>

#include "config.hpp"
#include "init.hpp"


FarmController farm_controller;


void setup() {
  init_serial();
  present_self_to_serial();
  web_server_init(&farm_controller);
  init_devices_io();
  Serial.printf("Connecting to %s\n", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}


void loop() {
  //digitalWrite(D0, HIGH);
  delay(1000);
  set_leds_color(0, 255, 0);
  web_server.handleClient();
}
