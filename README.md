WORK IN PROGRESS!

**Índice**   

- [DESCRIPCION](#descripcion)
- [INSTRUCCIONES](#instrucciones)
  - [OBTENER SHA1 FINGERPRINT](#obtener-sha1-fingerprint)
- [COMPILAR Y FLASHEAR](#compilar-y-flashear)
  - [FLASHEAR POR OTA](#flashear-por-ota)
- [CHANGELOG](#changelog)
- [RECONOCIMIENTOS](#reconocimientos)

# DESCRIPCION

Parte del sistema domotico del [Hangar2 Kreitek](http://kreitek.org) para permitir la entrada a los miembros con tarjeta RFID. Más informacion en la [wiki](http://wiki.kreitek.org/proyectos:domotica_con_sonoff_y_raspberry_pi)

# INSTRUCCIONES

- Clonar el repositorio
- En `src/config/` renombrar `userconfig_example.h` a `userconfig.h` y poner credenciales
- La placa por defecto es WEMOS D1 mini, para una placa diferente, cambiar en `platformio.ini`
- [Flashear la placa](#compilar-y-flashear)

## OBTENER SHA1 FINGERPRINT

- TODO

# COMPILAR Y FLASHEAR

- Se utiliza el IDE [platformio](https://platformio.org/platformio-ide)

## FLASHEAR POR OTA

- TODO

# CHANGELOG

[changelog en src/config/version.h](src/config/version.h)

# RECONOCIMIENTOS

Basado en [carontepass-v2](https://github.com/torehc/carontepass-v2) de [Héctor Figueras](https://github.com/torehc)
