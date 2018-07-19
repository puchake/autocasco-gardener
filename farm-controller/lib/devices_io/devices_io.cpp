#include <ESP8266WiFi.h>

#include "devices_io.hpp"


// Pinout for devices used in farm controller.
const uint8_t ADC_PIN = A0;
const uint8_t MUX_PIN_0 = D6;
const uint8_t MUX_PIN_1 = D7;
const uint8_t MUX_PIN_2 = D8;
const uint8_t PUMP_PIN = D0;


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
  Serial.printf("Water level: %d \n", analogRead(ADC_PIN));
  return in_voltage;
}


void set_multiplexer_channel(uint8_t channel) {
  digitalWrite(MUX_PIN_0, (channel & 0b00000001) > 0 ? HIGH : LOW);
  digitalWrite(MUX_PIN_1, (channel & 0b00000010) > 0 ? HIGH : LOW);
  digitalWrite(MUX_PIN_2, (channel & 0b00000100) > 0 ? HIGH : LOW);
  delayMicroseconds(1);
}


float inverse_water_height(float height) {
  const float offset = 0.42;
  return 1 / (height + offset);
}


float read_water_level() {
  const static float VOLTAGE_3_5 = 3.0;
  const static float VOLTAGE_6 = 2.0;
  const static float VOLTAGE_40 = 0.3;
  const static uint8_t WATER_LEVEL_SENSOR_CHANNEL = 0;
  set_multiplexer_channel(WATER_LEVEL_SENSOR_CHANNEL);
  float water_level_voltage = read_voltage_from_adc();
  Serial.printf("Water level: %f V\n", water_level_voltage);
  float water_height_inverse;
  if (water_level_voltage > VOLTAGE_6) {
    water_height_inverse = linear_interpolation(
      water_level_voltage, VOLTAGE_6, VOLTAGE_3_5, inverse_water_height(6),
      inverse_water_height(3.5)
    );
  }
  else {
    water_height_inverse = linear_interpolation(
      water_level_voltage, VOLTAGE_40, VOLTAGE_6, inverse_water_height(40),
      inverse_water_height(6)
    );
  }
  return 1 / water_height_inverse - 0.42;
}


void turn_pump_on() {
  digitalWrite(PUMP_PIN, HIGH);
}


void turn_pump_off() {
  digitalWrite(PUMP_PIN, LOW);
}
