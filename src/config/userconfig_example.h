// Renombrar como userconfig y rellenar (no se añadirá a git)

const char* WIFI_SSID = "nombredelawifi";
const char* WIFI_PASWORD = "contraseñadelawifi-ip";

const char* METAESPACIO_HOST = "https://metaespacio.kreitek.org";
const char* METAESPACIO_API_URL = "/caronte";

const char* SONOFF_IP = "192.168.1.78";
const char* SONOFF_USER = "admin";
const char* SONOFF_PASSWORD = "xxxxxxxx";


#define MQTT_BROKER "192.168.1.10" // ip o host del broker mqtt (mosquito)
#define MQTT_PORT 1883
#define DOMOTICZ_IN_TOPIC domoticz/in
#define DOMOTICZ_OUT_TOPIC outdomoticz/out
#define DOMOTICZ_IDX  34 // idx del interruptor virtual de domoticz que controlara la recreativa