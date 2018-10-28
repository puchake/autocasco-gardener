#include "web_server.hpp"


const char* WEB_SERVER_CONFIG_PATH = "/config";
const char* WEB_SERVER_STATUS_PATH = "/status";
const char* WEB_SERVER_READINGS_PATH = "/readings";
const uint16_t WEB_SERVER_PORT = 80;

const int JSON_BUFFER_SIZE = 512;


ESP8266WebServer web_server(WEB_SERVER_PORT);
FarmController* web_farm_controller;


void handle_config_get();
void handle_config_put();
void handle_status_get();
void handle_readings_get();


void web_server_init(FarmController* farm_controller) {
  web_farm_controller = farm_controller;
  web_server.on(WEB_SERVER_CONFIG_PATH, HTTP_GET, handle_config_get);
  web_server.on(WEB_SERVER_CONFIG_PATH, HTTP_PUT, handle_config_put);
  web_server.on(WEB_SERVER_STATUS_PATH, HTTP_GET, handle_status_get);
  web_server.on(WEB_SERVER_READINGS_PATH, HTTP_GET, handle_readings_get);
  web_server.begin();
}


void handle_config_get() {
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["pump_activation_water_level"] =
    web_farm_controller->get_farm_config().pump_activation_water_level;
  root["pump_deactivation_water_level"] =
    web_farm_controller->get_farm_config().pump_deactivation_water_level;
  root["no_water_warning_delay_ms"] =
    web_farm_controller->get_farm_config().no_water_warning_delay_ms;
  root["led_strip_red_intensity"] =
    web_farm_controller->get_farm_config().led_strip_red_intensity;
  root["led_strip_green_intensity"] =
    web_farm_controller->get_farm_config().led_strip_green_intensity;
  root["led_strip_blue_intensity"] =
    web_farm_controller->get_farm_config().led_strip_blue_intensity;
  String message;
  root.printTo(message);
  web_server.send(200, "application/json", message);
}


void handle_config_put() {
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  JsonObject &root = jsonBuffer.parseObject(web_server.arg("plain"));
  FarmConfig new_farm_config;
  new_farm_config.pump_activation_water_level =
    root["pump_activation_water_level"]
    | INITIAL_FARM_CONFIG.pump_activation_water_level;
  new_farm_config.pump_deactivation_water_level =
    root["pump_deactivation_water_level"]
    | INITIAL_FARM_CONFIG.pump_deactivation_water_level;
  new_farm_config.no_water_warning_delay_ms =
    root["no_water_warning_delay_ms"]
    | INITIAL_FARM_CONFIG.no_water_warning_delay_ms;
  new_farm_config.led_strip_red_intensity =
    root["led_strip_red_intensity"]
    | INITIAL_FARM_CONFIG.led_strip_red_intensity;
  new_farm_config.led_strip_green_intensity =
    root["led_strip_green_intensity"]
    | INITIAL_FARM_CONFIG.led_strip_green_intensity;
  new_farm_config.led_strip_blue_intensity =
    root["led_strip_blue_intensity"]
    | INITIAL_FARM_CONFIG.led_strip_blue_intensity;
  web_farm_controller->set_farm_config(new_farm_config);
  web_server.send(200, "text/plain", "Config updated succesfully.");
}


void handle_status_get() {
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["is_pump_on"] = web_farm_controller->get_farm_status().is_pump_on;
  String message;
  root.printTo(message);
  web_server.send(200, "application/json", message);
}


void handle_readings_get() {
  StaticJsonBuffer<JSON_BUFFER_SIZE> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["water_level"] = web_farm_controller->get_sensors_readings().water_level;
  String message;
  root.printTo(message);
  web_server.send(200, "application/json", message);
}
