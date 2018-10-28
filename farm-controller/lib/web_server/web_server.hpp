#ifndef __WEB_SERVER_HPP_INCLUDED__
#define __WEB_SERVER_HPP_INCLUDED__


#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#include <farm_state.hpp>
#include <farm_controller.hpp>


extern ESP8266WebServer web_server;


void web_server_init(FarmController* farm_controller);


#endif
