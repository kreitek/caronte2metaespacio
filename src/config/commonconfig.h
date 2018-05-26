#ifndef COMMONCONFIG_H
#define COMMONCONFIG_H

  #define OTA_TIMEOUT 15 * 60 * 1000 // tiempo que mantiene el modo ota (luego reinicia)
  #define SHA1_FINGERPRINT "CF 05 98 89 CA FF 8E D8 5E 5C E0 C2 E4 F7 E6 C3 C7 50 DD 5C"

  struct config_t {
    int   primerinicio;
    char  wifi_ssid[50];
    char  wifi_password[50];
    char  metaespacio_host[50];
    int   metaespacio_port;
    char  metaespacio_credentials[50];
    char  sonoff_ip[16];
    int   sonoff_port;
    char  sonoff_key[50];
  }; 

  extern config_t config;  

#endif
