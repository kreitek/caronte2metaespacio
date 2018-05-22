/*
#ifdef WEB_SERVER_V2
#include <Arduino.h>
//#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include "web_form.h"

#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>

AsyncWebServer * _server;


void webServerSetup(){
    // Create server
    unsigned int port = 80;
    _server = new AsyncWebServer(port);

    // Rewrites
    _server->rewrite("/", "/index.html");

    _server->on("/config", HTTP_POST | HTTP_PUT, _onPostConfig, _onPostConfigData);
}

void _onPostConfig(AsyncWebServerRequest *request) {
    webLog(request);
    if (!_authenticate(request)) return request->requestAuthentication(getSetting("hostname").c_str());
    request->send(_webConfigSuccess ? 200 : 400);
}
#endif
*/