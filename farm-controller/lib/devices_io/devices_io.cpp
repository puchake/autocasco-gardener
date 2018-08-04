#include <ESP8266WiFI.h>

#include "devices_io.hpp"


// Pinout for devices used in farm controller.
const uint8_t ADC_PIN = A0;
const uint8_t MUX_PIN_0 = D6;
const uint8_t MUX_PIN_1 = D7;
const uint8_t MUX_PIN_2 = D8;
const uint8_t PUMP_PIN = D0;

const float WATER_SENSOR_VOLTAGES[] = {0.54, 0.6, 0.76, 0.96, 1.31, 2.38, 2.85,
                                       3.08};
const float WATER_SENSOR_HEIGHTS[] = {30, 25, 20, 15, 10, 5, 4, 3.5};
const int WATER_SENSOR_VOLTAGES_COUNT = 8;
const float WATER_SENSOR_BOTTOM_DISTANCE = 40.0;


void init_devices_io() {
  pinMode(ADC_PIN, INPUT);
  pinMode(MUX_PIN_0, OUTPUT);
  pinMode(MUX_PIN_1, OUTPUT);
  pinMode(MUX_PIN_2, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
}


float linear_interpolation(
  float x, float x_1, float x_2, float y_1, float y_2
) {
  return y_1 + (y_2 - y_1) / (x_2 - x_1) * (x - x_1);
}


float read_voltage_from_adc() {
  const static float REFERENCE_ADC_VOLTAGE = 3.25;
  const static uint16_t ADC_MAX = 1024;
  float in_voltage = REFERENCE_ADC_VOLTAGE * analogRead(ADC_PIN) / ADC_MAX;
  return in_voltage;
}


void set_multiplexer_channel(uint8_t channel) {
  digitalWrite(MUX_PIN_0, (channel & 0b00000001) > 0 ? HIGH : LOW);
  digitalWrite(MUX_PIN_1, (channel & 0b00000010) > 0 ? HIGH : LOW);
  digitalWrite(MUX_PIN_2, (channel & 0b00000100) > 0 ? HIGH : LOW);
  delayMicroseconds(1);
}


float read_sensor_value(const float voltages[], const float values[],
                        int voltages_count, float current_voltage) {
  if (current_voltage <= voltages[0]) {
    return values[0];
  }
  for (int i = 1; i < voltages_count; i++) {
    if (current_voltage <= voltages[i]) {
      return linear_interpolation(current_voltage, voltages[i - 1],
                                  voltages[i], values[i - 1], values[i]);
    }
  }
  return values[voltages_count - 1];
}


float read_water_level() {
  const static uint8_t WATER_LEVEL_SENSOR_CHANNEL = 0;
  set_multiplexer_channel(WATER_LEVEL_SENSOR_CHANNEL);
  float water_level_voltage = read_voltage_from_adc();
  return WATER_SENSOR_BOTTOM_DISTANCE
         - read_sensor_value(WATER_SENSOR_VOLTAGES, WATER_SENSOR_HEIGHTS,
                             WATER_SENSOR_VOLTAGES_COUNT, water_level_voltage);
}


void turn_pump_on() {
  digitalWrite(PUMP_PIN, HIGH);
}


void turn_pump_off() {
  digitalWrite(PUMP_PIN, LOW);
}
