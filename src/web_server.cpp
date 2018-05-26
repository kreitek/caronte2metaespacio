#include "web_server.h"
#include "web_form.h"

WiFiServer server(80);

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
    static bool exito_reiniciar = false;
    if(exito_reiniciar){
        delay(100);
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
  /*
  while(!client.available()){
    delay(1);
  }
  */
    delay(10);
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  
  // Match the request
  // if (req.indexOf("/api") != -1)
    if (req.indexOf("GET") != -1){
        mostrar_formulario(client);
    }
    else if (req.indexOf("POST") != -1){
        if(comprobar_respuesta(client)){
            exito_reiniciar = true;            
        }
        else{
            // TODO mensaje de error
            mostrar_formulario(client);
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
  // client.stop();
}

void mostrar_formulario(WiFiClient &client){
    client.print(web_header);
    client.print(web_html_inicio);
    client.print(web_css);
    client.print(web_html_tras_css);
    client.print(web_form_inicio);
    client.print(web_form_wifi_ssid);
    client.print(config.wifi_ssid);
    client.print(web_form_label_fin);
    client.print(web_form_wifi_password);
    client.print(web_form_label_fin);
    client.print(web_form_metaespacio_host);
    client.print(config.metaespacio_host);
    client.print(web_form_label_fin);
    client.print(web_form_metaespacio_port);
    client.print(config.metaespacio_port);
    client.print(web_form_label_fin);
    client.print(web_form_metaespacio_credentials);
    client.print(config.metaespacio_credentials);
    client.print(web_form_label_fin);
    client.print(web_info_credentials);
    client.print(web_form_sonoff_ip);
    client.print(config.sonoff_ip);
    client.print(web_form_label_fin);
    client.print(web_form_sonoff_port);
    client.print(config.sonoff_port);
    client.print(web_form_label_fin);
    client.print(web_form_sonoff_key);
    client.print(config.sonoff_key);
    client.print(web_form_label_fin);
    client.print(web_form_fin);
    client.print(web_html_fin);
}

bool comprobar_respuesta(WiFiClient &client){

    String req;
    bool cabecera_encontrada = false;
    while (client.available()) {
        if(!cabecera_encontrada){
            req = client.readStringUntil('\r');
            //Serial.print(req);
            if (req.length() < 2){ // Fin de cabecera
                cabecera_encontrada = true;
                req = "";
            }
        }
        else{
            //req += String();
            char chr = (char)client.read();
            req.concat(chr);
        }

    }
    if (!cabecera_encontrada)
        return false;

    // Confirmamos cuanto antes que se ha recibido la respuesta del formulario
    client.print(web_header);
    client.print(web_enviado);

    req.trim();
    /*
    Serial.println("req============");
    Serial.println(req);
    Serial.println("req============");
*/
    int pos_wifi_ssid = req.indexOf("wifi_ssid=");
    int pos_wifi_password = req.indexOf("wifi_password=");
    int pos_metaespacio_host = req.indexOf("metaespacio_host=");
    int pos_metaespacio_port = req.indexOf("metaespacio_port=");
    int pos_metaespacio_credentials = req.indexOf("metaespacio_credentials=");
    int pos_sonoff_ip = req.indexOf("sonoff_ip=");
    int pos_sonoff_port = req.indexOf("sonoff_port=");
    int pos_sonoff_key = req.indexOf("sonoff_key=");

    if (pos_wifi_ssid == -1 || pos_wifi_password == -1 || pos_metaespacio_host == -1){
        Serial.println("Error en el post");
        return false;
    }

    String str_wifi_ssid = req.substring(pos_wifi_ssid + 10, pos_wifi_password -1);
    str_wifi_ssid.trim();
    String str_wifi_password = req.substring(pos_wifi_password + 14, pos_metaespacio_host -1);
    str_wifi_password.trim();
    String str_metaespacio_host = req.substring(pos_metaespacio_host + 17, pos_metaespacio_port -1);
    str_metaespacio_host.trim();
    String str_metaespacio_port = req.substring(pos_metaespacio_port + 17, pos_metaespacio_credentials -1);
    String str_metaespacio_credentials = req.substring(pos_metaespacio_credentials + 24, pos_sonoff_ip -1);
    str_metaespacio_credentials.trim();
    String str_sonoff_ip = req.substring(pos_sonoff_ip + 10, pos_sonoff_port -1);
    str_sonoff_ip.trim();
    String str_sonoff_port = req.substring(pos_sonoff_port + 12, pos_sonoff_key -1);
    String str_sonoff_key = req.substring(pos_sonoff_key + 11);
    str_sonoff_key.trim();

    strcpy(config.wifi_ssid, str_wifi_ssid.c_str());
    // no se muestra contraseña, asi que solo actualiza si se ha escrito algo
    if (str_wifi_password.length()>3)
    strcpy( config.wifi_password, str_wifi_password.c_str());
    strcpy( config.metaespacio_host, str_metaespacio_host.c_str());
    config.metaespacio_port = atoi (str_metaespacio_port.c_str());
    strcpy( config.metaespacio_credentials, str_metaespacio_credentials.c_str());
    strcpy( config.sonoff_ip, str_sonoff_ip.c_str());
    config.sonoff_port = atoi (str_sonoff_port.c_str());
    strcpy( config.sonoff_key, str_sonoff_key.c_str());

    Serial.print("wifi_ssid: ");
    Serial.println(config.wifi_ssid);
    Serial.print("wifi_password: ");
    Serial.println(config.wifi_password);
    Serial.print("metaespacio_host: ");
    Serial.println(config.metaespacio_host);
    Serial.print("metaespacio_port: ");
    Serial.println(config.metaespacio_port);
    Serial.print("metaespacio_credentials: ");
    Serial.println(config.metaespacio_credentials);
    Serial.print("sonoff_ip: ");
    Serial.println(config.sonoff_ip);
    Serial.print("sonoff_port: ");
    Serial.println(config.sonoff_port);
    Serial.print("sonoff_key: ");
    Serial.println(config.sonoff_key);

    eeprom_guardar_configuracion();
    return true;
}
