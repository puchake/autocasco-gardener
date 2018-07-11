#include <ESP8266WiFi.h>

#include "sensors.hpp"
#include "config.hpp"

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

