#include <Arduino.h>
#include "MFRC522.h"
#include "config/all.h"


boolean lasttagaccepted;
unsigned long lasttime;

int _tag[4];

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    // Serial.print(buffer[i] < 0x10 ? "" : ".");
    // Serial.print(buffer[i], DEC);
    _tag[i] = buffer[i];
  }
}

void playbuzzer(){
  analogWrite(BUZZER, 180);
  delay(750);
  analogWrite(BUZZER, 0);
}

void setup() {
  // IO configuration
  pinMode(BUZZER, OUTPUT);
  pinMode(BUZZER_GND, OUTPUT);
  analogWrite(BUZZER, 0);
  digitalWrite(BUZZER_GND, LOW);
  // Initialize serial communications
  Serial.begin(115200);
  delay(10);
  SPI.begin();           // Init SPI bus
  mfrc522.PCD_Init();    // Init MFRC522

  wifiSetup();
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }
  playbuzzer();
  // Show some details of the PICC (that is: the tag/card)
  Serial.println("RFID Tag Detected...");
  // Formateamos la respuesta
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

  char tag_str[9];  // almacena los 4 bytes del tag en formato hex seguidos.
  sprintf(tag_str, "%02hX%02hX%02hX%02hX", _tag[0], _tag[1], _tag[2], _tag[3]); // Ej: C6E30F1B
  DEBUGPRINT("Tarjeta: %s\n", tag_str);

  if(is_card_allowed(tag_str)){
    DEBUGPRINT("Entrance allowed\n");
    disparar_sonoff();
  }
  else{
    DEBUGPRINT("Entrance NOT allowed\n");
    //beeperror(); TODO
  }

  // Avoid two cards in a short period
  delay(3000);
}
