#define OTA_TIMEOUT 10 * 60 * 1000 // tiempo que mantiene el modo ota (luego reinicia)

  struct config_t {
    char  wifi_ssd[50];
    char  wifi_password[50];
    char  metaespacio_host[50];
    int   metaespacio_port;
    char  metaespacio_api_url[50];
  } config; 