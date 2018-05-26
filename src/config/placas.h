
#ifdef WEMOS
  /*
  * PINOUT
  * +--------------------------------+-----------------------+
  * | WEMOS D1 ESP8266 BOARD         |    CONECT TO PIN      |
  * +--------------------------------+---------------+-------+
  * | PIN  | FUCTION  | ESP-8266 PIN | RC522 | RELAY | BUZZER|
  * +------+----------+--------------+-------+-------+-------+
  * | 3.3V | POWER    | 3.3V         | 3.3V  |       |       |
  * +------+----------+--------------+-------+-------+-------+
  * | 5V   | POWER    | 5V           |       | VCC   |       |
  * +------+----------+--------------+-------+-------+-------+
  * | GND  | GND      | GND          | GND   | GND   |       |
  * +------+----------+--------------+-------+-------+-------+
  * | D13  | SCK      | GPIO-14      | SCK   |       |       |
  * +------+----------+--------------+-------+       +-------+
  * | D12  | MISO     | GPIO-12      | MISO  |       |       |
  * +------+----------+--------------+-------+       +-------+
  * | D11  | MOSI     | GPIO-13      | MOSI  |       |       |
  * +------+----------+--------------+-------+       +-------+
  * | D10  | SS (SDA) | GPIO-15      | SDA   |       |       |
  * +------+----------+--------------+-------+       +-------+
  * | D8   | IO       | GPIO-0       | RESET |       |       |
  * +------+----------+--------------+-------+-------+-------+
  * | D0   | IO       | GPIO-16      |       | IN1   |       |
  * +------+----------+--------------+-------+-------+-------+
  * | D1   | PWM      | GPIO-5       |       |       | Red   |
  * +------+----------+--------------+-------+-------+-------+
  * | D2   | GROUND   | GPIO-4       |       |       | Black |
  * +------+----------+--------------+-------+-------+-------+
  */

  #define RST_PIN   0 // RST-PIN for RC522 - RFID - SPI - Module GPIO-0
  #define SS_PIN    15  // SDA-PIN for RC522 - RFID - SPI - Module GPIO-15
  #define BUZZER    5 // D1
  #define BUZZER_GND  4 // D2, just to ground all the time

  #define PULSADOR_CONFIG  D4 // CUIDADO no todos los pines de weemos tienen pullups
  #define PULSADOR_CONFIG_MODO INPUT_PULLUP
  #define PULSADOR_CONFIG_PULSADO  LOW
  // 2 D4 LED
#endif
