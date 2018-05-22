#include <Arduino.h>
//#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include "config/all.h"
#include "eeprom_func.h"

extern WiFiServer server;

bool comprobar_respuesta(WiFiClient &client);
void webServerSetup();
void webServerLoop();
void mostrar_formulario(WiFiClient &client);
