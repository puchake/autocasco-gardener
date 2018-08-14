#ifndef __STATE_HPP_INCLUDED__
#define __STATE_HPP_INCLUDED__


#include <ESP8266WiFI.h>


struct FarmStatus {
  bool is_pump_on;
  // TODO: add the rest of the status
};


struct FarmConfig {
  float pump_activation_water_level;
  float pump_deactivation_water_level;
  int no_water_warning_delay_ms;

  uint8_t led_strip_red_intensity;
  uint8_t led_strip_green_intensity;
  uint8_t led_strip_blue_intensity;
  // TODO: add the rest of the config
};


struct SensorsReadings {
  float water_level;
  // TODO: add the rest of the readings
};


extern const FarmStatus INITIAL_FARM_STATUS;
extern const FarmConfig INITIAL_FARM_CONFIG;
extern const SensorsReadings INITIAL_SENSORS_READINGS;


#endif
