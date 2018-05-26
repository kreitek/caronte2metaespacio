#include <EEPROM.h>
#include <Arduino.h>

void storeStruct(void *data_source, size_t size);
void loadStruct(void *data_dest, size_t size);
void eeprom_guardar_configuracion();
void eeprom_leer_configuracion();
void iniciar_eeprom();
