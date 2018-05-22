#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>


bool is_card_allowed(char* tag){
  WiFiClient client;
  if (!client.connect(config.metaespacio_host, config.metaespacio_port)) {
    DEBUGPRINT("connection failed\n");
    return false;
  }
  
  // This will send the request to the server
  /*
  client.println(
    String("GET ") + url + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" + "Authorization: Basic " + userpass + "\r\n" + 
    "Connection: close\r\n\r\n");
  */

  client.println(
    String("GET ") + config.metaespacio_api_url + tag + " HTTP/1.1\r\n" +
    "Host: " + config.metaespacio_host + "\r\n" + 
    "Connection: close\r\n\r\n");

  delay(10);
  
  while(client.connected()){
    String line = client.readStringUntil('\r');
    line.trim();
    DEBUGPRINT("%s\n", line.c_str());
    if (strstr ( line.c_str(), "HTTP/1.0" ) != NULL) {
      if (strstr ( line.c_str(), "200 OK" ) != NULL) 
        return true;
      else
        return false;
    }

    
  }
  client.stop();
  return false;
}

void wifiSetup() {
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(config.wifi_ssd);
  WiFi.mode(WIFI_STA);
  WiFi.begin(config.wifi_ssd, config.wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (comprobar_modoconfig())
      return;
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void https_ejemplo() {
  /*
 *  HTTP over TLS (HTTPS) example sketch
 *
 *  This example demonstrates how to use
 *  WiFiClientSecure class to access HTTPS API.
 *  We fetch and display the status of
 *  esp8266/Arduino project continuous integration
 *  build.
 *
 *  Created by Ivan Grokhotkov, 2015.
 *  This example is in public domain.
 */

  const int httpsPort = 443;

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(config.metaespacio_host);
  if (!client.connect(config.metaespacio_host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(SHA1_FINGERPRINT, config.metaespacio_host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  String url = "FF:FF:FF:FF:FF:FF";
  Serial.print("requesting URL: ");
  Serial.println(url);

  url = "";

  client.print(String("GET ") + config.metaespacio_api_url + url + " HTTP/1.1\r\n" +
               "Host: " + config.metaespacio_host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
}


