#include "web_server.hpp"
#include "config.hpp"


ESP8266WebServer web_server(80);


void web_server_init() {
  web_server.on(WEB_SERVER_CONFIG_PATH, HTTP_GET, handle_config_get);
  web_server.on(WEB_SERVER_CONFIG_PATH, HTTP_PUT, handle_config_put);
  web_server.on(WEB_SERVER_STATUS_PATH, HTTP_GET, handle_status_get);
  web_server.begin();
}

void handle_config_get() {
  // TODO: return current config in message body.
  web_server.send(200, "text/plain", "Example config.");
}

void handle_config_put() {
  // TODO: parse request body, handle syntax errors and update config accordingly.
  web_server.send(200, "text/plain", "Example put successful.");
}

void handle_status_get() {
  // TODO: return readings from sensors and farm status in message body.
  web_server.send(200, "text/plain", "Example status.");
}

void respond_with_syntax_error() {
  // TODO: implement a function to respond to client on syntax error in config on HTTP_PUT.
}
