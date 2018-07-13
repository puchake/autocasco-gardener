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
  const static float REFERENCE_ADC_VOLTAGE = 3;
  const static uint16_t ADC_MAX = 1023;
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


float read_water_level() {
  const static float VOLTAGES[] = {0.0, 1.3, 1.53, 1.62, 1.69, 1.74, 1.77,
                                   1.81, 1.84, 1.86, 1.88};
  const static float HEIGHTS[] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0,
                                  4.5, 4.8};
  const static uint8_t MEASUREMENT_SET_SIZE = 11;
  const static uint8_t WATER_LEVEL_SENSOR_CHANNEL = 0;
  set_multiplexer_channel(WATER_LEVEL_SENSOR_CHANNEL);
  float water_level_voltage = read_voltage_from_adc();
  //Serial.printf("Water level: %f V\n", water_level_voltage);
  for (int i = 1; i < MEASUREMENT_SET_SIZE; i++) {
    if (water_level_voltage <= VOLTAGES[i]) {
      return linear_interpolation(water_level_voltage, VOLTAGES[i - 1],
                                  VOLTAGES[i], HEIGHTS[i - 1], HEIGHTS[i]);
    }
  }
  return HEIGHTS[MEASUREMENT_SET_SIZE - 1];
}


void turn_pump_on() {
  digitalWrite(PUMP_PIN, HIGH);
}


void turn_pump_off() {
  digitalWrite(PUMP_PIN, LOW);
}
