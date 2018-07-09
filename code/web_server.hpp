#ifndef __WEB_SERVER_HPP_INCLUDED__   
#define __WEB_SERVER_HPP_INCLUDED__   


#include <ESP8266WebServer.h>


extern ESP8266WebServer web_server;


void web_server_init();

void handle_config_get();
void handle_config_put();

void handle_status_get();

void respond_with_syntax_error();

#endif 
