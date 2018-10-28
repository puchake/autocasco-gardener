#include <devices_io.hpp>

#include "farm_controller.hpp"


FarmController::FarmController() {
  farm_status = INITIAL_FARM_STATUS;
  farm_config = INITIAL_FARM_CONFIG;
  sensors_readings = INITIAL_SENSORS_READINGS;
}


void FarmController::make_control_step() {
  update_sensors_readings();
  control_pump();
  control_led_strip();
}


void FarmController::update_sensors_readings() {
  sensors_readings.water_level = read_water_level();
}


SensorsReadings FarmController::get_sensors_readings() {
  return sensors_readings;
}


FarmStatus FarmController::get_farm_status() {
  return farm_status;
}


FarmConfig FarmController::get_farm_config() {
  return farm_config;
}


void FarmController::set_farm_config(FarmConfig farm_config) {
  this->farm_config = farm_config;
}


void FarmController::activate_pump() {
  farm_status.is_pump_on = true;
  turn_pump_on();
}


void FarmController::deactivate_pump() {
  farm_status.is_pump_on = false;
  turn_pump_off();
}


void FarmController::control_pump() {
  if (sensors_readings.water_level <= farm_config.pump_activation_water_level) {
    turn_pump_on();
  }
  if (sensors_readings.water_level
      >= farm_config.pump_deactivation_water_level) {
    turn_pump_off();
  }
}


void FarmController::control_led_strip() {
  set_leds_color(farm_config.led_strip_red_intensity,
                 farm_config.led_strip_green_intensity,
                 farm_config.led_strip_blue_intensity);
}
