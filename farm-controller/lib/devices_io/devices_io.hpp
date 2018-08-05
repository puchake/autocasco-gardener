#ifndef __SENSORS_HPP_INCLUDED__
#define __SENSORS_HPP_INCLUDED__


#include <ESP8266WiFI.h>


void init_devices_io();

float read_water_level();
void turn_pump_on();
void turn_pump_off();

void set_leds_color(uint8_t red, uint8_t green, uint8_t blue);
void turn_leds_off();


#endif
