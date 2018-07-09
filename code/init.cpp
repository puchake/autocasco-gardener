#include <ESP8266WiFi.h>

#include "init.hpp"
#include "config.hpp"

void init_serial() {
  Serial.begin(SERIAL_BAUD_RATE);
  delay(SERIAL_INIT_DELAY_MS);
  Serial.printf("Serial setup complete.\n");
}

void present_self_to_serial() {
  Serial.printf("########## ESP8266 ##########\n");
  Serial.printf("ID: %d\n", ESP.getChipId());
  Serial.printf("CPU freq: %d Mhz\n", ESP.getCpuFreqMHz());
  Serial.printf("Flash ID: %d\n", ESP.getFlashChipId());
  Serial.printf("Flash size: %d B\n", ESP.getFlashChipSize());
  Serial.printf("Flash real size: %d B\n", ESP.getFlashChipRealSize());
  Serial.printf("#############################\n");
}

