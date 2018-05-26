#include "eeprom_func.h"
#include "config/all.h"


void storeStruct(void *data_source, size_t size)
{
  EEPROM.begin(size * 2);
  for(size_t i = 0; i < size; i++)
  {
    char data = ((char *)data_source)[i];
    EEPROM.write(i, data);
  }
  EEPROM.commit();
}

void loadStruct(void *data_dest, size_t size)
{
    EEPROM.begin(size * 2);
    for(size_t i = 0; i < size; i++)
    {
        char data = EEPROM.read(i);
        ((char *)data_dest)[i] = data;
    }
}

void eeprom_guardar_configuracion(){
    storeStruct(&config, sizeof(config));
}

void eeprom_leer_configuracion(){
    loadStruct(&config, sizeof(config));
    if (config.primerinicio != 0xABCD)
        iniciar_eeprom();
    // Debug
    /*
    Serial.print("wifi_ssid: '");
    Serial.print(config.wifi_ssid);
    Serial.println("'");
    //Serial.print("wifi_password: '");
    //Serial.print(config.wifi_password);
    //Serial.println("'");
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
    */
}

void iniciar_eeprom(){
    DEBUGPRINT("EEPROM vacia, rellenando...\n");
    // Valores por defecto
    config.primerinicio = 0xABCD;
    strcpy(config.wifi_ssid, "");
    strcpy( config.wifi_password, "");
    strcpy( config.metaespacio_host, "");
    config.metaespacio_port = 80;
    strcpy( config.metaespacio_credentials, "");
    strcpy( config.sonoff_ip, "");
    config.sonoff_port = 5000;
    strcpy( config.sonoff_key, "");

    eeprom_guardar_configuracion();
}