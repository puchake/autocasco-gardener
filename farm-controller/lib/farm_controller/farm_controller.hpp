#ifndef __FARM_CONTROLLER_HPP_INCLUDED__
#define __FARM_CONTROLLER_HPP_INCLUDED__


#include <farm_state.hpp>


class FarmController {

public:
  FarmController();
  void make_control_step();
  SensorsReadings get_sensors_readings();
  FarmStatus get_farm_status();
  FarmConfig get_farm_config();
  void set_farm_config(FarmConfig farm_config);

private:
  FarmStatus farm_status;
  FarmConfig farm_config;
  SensorsReadings sensors_readings;


  void update_sensors_readings();
  void activate_pump();
  void deactivate_pump();
  void control_pump();
  void control_led_strip();

};

#endif
