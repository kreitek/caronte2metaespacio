#include <Arduino.h>
#include "MFRC522.h"
#include "config/all.h"


int tag[4];
boolean lasttagaccepted;
unsigned long lasttime;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? "" : ".");
    Serial.print(buffer[i], DEC);
    tag[i] = buffer[i];
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
  Serial.print(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();

  // We now create a URI for the request
  String url = "/api/1/device/";
  url += tag[0];
  url += ".";
  url += tag[1];
  url += ".";
  url += tag[2];
  url += ".";
  url += tag[3];

  DEBUGPRINT("Requesting URL %s\n", url.c_str());

  if(is_card_allowed()){
    // open_door(); TODO
  }
  else{
    DEBUGPRINT("Entrance not allowed\n");
    //beeperror(); TODO
  }

  // Avoid two cards in a short period
  delay(3000);
}
