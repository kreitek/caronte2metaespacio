**Índice**   

- [DESCRIPCION](#descripcion)
- [INSTRUCCIONES](#instrucciones)
- [COMPILAR Y FLASHEAR](#compilar-y-flashear)
  - [FLASHEAR POR OTA](#flashear-por-ota)
- [CONFIGURACION](#configuracion)
- [CHANGELOG](#changelog)
- [RECONOCIMIENTOS](#reconocimientos)

# DESCRIPCION

Parte del sistema domotico del [Hangar2 Kreitek](http://kreitek.org) para permitir la entrada a los miembros con tarjeta RFID. Más informacion en la [wiki](http://wiki.kreitek.org/proyectos:domotica_con_sonoff_y_raspberry_pi)

# INSTRUCCIONES

- Clonar el repositorio
- La placa por defecto es WEMOS D1 mini, para una placa diferente, cambiar en `platformio.ini`
- [Flashear la placa](#compilar-y-flashear)
- [Configurar](#configuracion)

# COMPILAR Y FLASHEAR

- Se utiliza el IDE [platformio](https://platformio.org/platformio-ide)

## FLASHEAR POR OTA

- Una vez flasheado, se puede actualizar por OTA:
- Pulsar boton configuracion (pin PULSADOR_CONFIG a gnd), conectarse a la wifi del ESP, desde un terminal ejecutar
```pio run -t upload -e wemos-ota```

# CONFIGURACION

- Pulsar boton configuracion (pin PULSADOR_CONFIG a gnd)
- El ESP se pone en modo AP, conectarse a la wifi del ESP (no tiene contraseña)
- En un navegador entrar en la direccion 192.168.1.4
- Poner datos y guardar

# CHANGELOG

[changelog en src/config/version.h](src/config/version.h)

# RECONOCIMIENTOS

Basado en [carontepass-v2](https://github.com/torehc/carontepass-v2) de [Héctor Figueras](https://github.com/torehc)
