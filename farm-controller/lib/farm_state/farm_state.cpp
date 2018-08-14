#include "farm_state.hpp"


const FarmStatus INITIAL_FARM_STATUS = {
  is_pump_on: false
};

const FarmConfig INITIAL_FARM_CONFIG = {
  pump_activation_water_level: 10.0,
  pump_deactivation_water_level: 15.0,
  no_water_warning_delay_ms: 5000,
  led_strip_red_intensity: 255,
  led_strip_green_intensity: 0,
  led_strip_blue_intensity: 255
};

const SensorsReadings INITIAL_SENSORS_READINGS = {
  water_level: 12.5
};
