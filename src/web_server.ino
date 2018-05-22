#include <Arduino.h>
//#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include "web_form.h"

WiFiServer server(80);

bool comprobar_respuesta(WiFiClient&);

void webServerSetup(){
  WiFi.softAP(APP_NAME);
  delay(100);
  IPAddress myIP = WiFi.softAPIP(); // IP 192.168.4.1
  server.begin();
  Serial.print("Iniciado servidor en ");
  Serial.print(myIP);
  Serial.println(":80");
}



void webServerLoop(){
    static bool guardado_con_exito = false;
    if(guardado_con_exito){ 
     ESP.restart();
    }

    WiFiClient client;

  // Check if a client has connected
  client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  // if (req.indexOf("/api") != -1)
    if (req.indexOf("GET") != -1){
        client.print(web_header);
        client.print(web_html_inicio);
        client.print(web_css);
        client.print(web_html_tras_css);
        client.print(web_form_inicio);
        client.print(web_form_wifi_ssd);
        client.print(config.wifi_ssd);
        client.print(web_form_label_fin);
        client.print(web_form_wifi_password);
        client.print(web_form_label_fin);
        client.print(web_form_metaespacio_host);
        client.print(config.metaespacio_host);
        client.print(web_form_label_fin);
        client.print(web_form_metaespacio_port);
        client.print(config.metaespacio_port);
        client.print(web_form_label_fin);
        client.print(web_form_metaespacio_api_url);
        client.print(config.metaespacio_api_url);
        client.print(web_form_label_fin);
        client.print(web_form_fin);
        client.print(web_html_fin);
    }
    else if (req.indexOf("POST") != -1){
        if(comprobar_respuesta(client)){
            client.print(web_header);
            client.print(web_enviado);
            guardado_con_exito = true;            
        }
        else{
            // TODO mensaje de error
            // mostrar_formulario();
        }
    }
    else {
        Serial.println("invalid request");
        client.stop();
        return;
    }
  client.flush();

  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
  //client.stop();
}

void mostrar_formulario(){

}

bool comprobar_respuesta(WiFiClient& client2){

    String req;
    bool cabecera_encontrada = false;
    while (client2.available()) {
        req = client2.readStringUntil('\r');
        //Serial.print(req);
        if (cabecera_encontrada)
            break;
        else if (req.length() < 2){ // Fin de cabecera
            cabecera_encontrada = true;
        }
    }
    if (!cabecera_encontrada)
        return false;
    Serial.println("ultima linea============");
    Serial.println(req);

    int pos_wifi_ssd = req.indexOf("wifi_ssd=");
    int pos_wifi_password = req.indexOf("wifi_password=");
    int pos_metaespacio_host = req.indexOf("metaespacio_host=");
    int pos_metaespacio_port = req.indexOf("metaespacio_port=");
    int pos_metaespacio_api_url = req.indexOf("metaespacio_api_url=");


    if (pos_wifi_ssd == -1 || pos_wifi_password == -1 || pos_metaespacio_host == -1){
        Serial.println("Error en el post");
        return false;
    }

    String str_wifi_ssd = req.substring(pos_wifi_ssd + 9, pos_wifi_password -1);
    String str_wifi_password = req.substring(pos_wifi_password + 14, pos_metaespacio_host -1);
    String str_metaespacio_host = req.substring(pos_metaespacio_host + 17, pos_metaespacio_port -1);
    String str_metaespacio_port = req.substring(pos_metaespacio_port + 17, pos_metaespacio_api_url -1);
    String str_metaespacio_api_url = req.substring(pos_metaespacio_api_url + 20);
    str_metaespacio_api_url.trim();

    strcpy(config.wifi_ssd, str_wifi_ssd.c_str());
    // no se muestra contraseña, asi que solo actualiza si se ha escrito algo
    if (str_wifi_password.length()>3)
        strcpy( config.wifi_password, str_wifi_password.c_str());
    strcpy( config.metaespacio_host, str_metaespacio_host.c_str());
    config.metaespacio_port = atoi (str_metaespacio_port.c_str());
    strcpy( config.metaespacio_api_url, str_metaespacio_api_url.c_str());

    Serial.print("wifi_ssd: ");
    Serial.println(config.wifi_ssd);
    Serial.print("wifi_password: ");
    Serial.println(config.wifi_password);
    Serial.print("metaespacio_host: ");
    Serial.println(config.metaespacio_host);
    Serial.print("metaespacio_port: ");
    Serial.println(config.metaespacio_port);
    Serial.print("metaespacio_api_url: ");
    Serial.println(config.metaespacio_api_url);

    eeprom_guardar_configuracion();
    return true;
}
