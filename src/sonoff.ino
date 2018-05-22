#include <ESP8266WiFi.h>

bool disparar_sonoff(){
    WiFiClient client;
    if (!client.connect(config.sonoff_ip, config.sonoff_port)) {
        DEBUGPRINT("connection failed\n");
        return false;
    }
    client.print(String("GET /api/relay/0?apikey=") + config.sonoff_key + "&value=1 HTTP/1.1\r\n" + 
        "Host: " + config.sonoff_ip + "\r\n" + 
        "Connection: close\r\n\r\n");

    while(client.connected()){
        String line = client.readStringUntil('\r');
        // Serial.print(line);
    }
    return true;
}
