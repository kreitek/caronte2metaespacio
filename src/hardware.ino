void hardwareSetup(){
    pinMode(PULSADOR_CONFIG, PULSADOR_CONFIG_MODO);

    pinMode(BUZZER, OUTPUT);
    pinMode(BUZZER_GND, OUTPUT);

    analogWrite(BUZZER, 0);
    digitalWrite(BUZZER_GND, LOW);
}

void playbuzzer(){
  analogWrite(BUZZER, 180);
  delay(750);
  analogWrite(BUZZER, 0);
}
