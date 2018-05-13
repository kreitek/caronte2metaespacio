#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>


bool is_card_allowed(char* tag){
  WiFiClient client;
  if (!client.connect(METAESPACIO_HOST, METAESPACIO_PORT)) {
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
    String("GET ") + METAESPACIO_API_URL + tag + " HTTP/1.1\r\n" +
    "Host: " + METAESPACIO_HOST + "\r\n" + 
    "Connection: close\r\n\r\n");

  delay(10);
  
  while(client.connected()){
    String line = client.readStringUntil('\r');
    //Serial.println(line);
    String result = line.substring(1,2);
    
    if (result=="[") //detects the beginning of the string json
    {
      Serial.print("Response: ");
      Serial.println(line);

      if (line.indexOf("true") >= 0 )
      {
        Serial.println("Access Granted");
        Serial.println("Relay Activated");
        delay(1500);
        return true;
       }
       else if (line.indexOf("null") >= 0 )
       {
        Serial.println("Access Unidentified");
       }
       else{
          Serial.println("False");
        }
    }
    
  }
  return false;
}

void wifiSetup() {
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
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
  Serial.println(METAESPACIO_HOST);
  if (!client.connect(METAESPACIO_HOST, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(SHA1_FINGERPRINT, METAESPACIO_HOST)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  String url = "FF:FF:FF:FF:FF:FF";
  Serial.print("requesting URL: ");
  Serial.println(url);

  url = "";

  client.print(String("GET ") + METAESPACIO_API_URL + url + " HTTP/1.1\r\n" +
               "Host: " + METAESPACIO_HOST + "\r\n" +
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


