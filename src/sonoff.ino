#include <ESP8266WiFi.h>


bool disparar_sonoff(){
    WiFiClient client;
    if (!client.connect(SONOFF_IP, SONOFF_PORT)) {
        DEBUGPRINT("connection failed\n");
        return false;
    }
    client.print(String("GET /api/relay/0?apikey=") + SONOFF_KEY + "&value=1 HTTP/1.1\r\n" + 
        "Host: " + SONOFF_IP + "\r\n" + 
        "Connection: close\r\n\r\n");

    while(client.connected()){
        String line = client.readStringUntil('\r');
        // Serial.print(line);
    }
    return true;
}