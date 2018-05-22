#define DEBUGOUTPUTSERIAL 1
#define DEBUGOUTPUTTELNET 2

extern char bufferprint[500]; // Para imprimir

#if DEBUGOUTPUT == DEBUGOUTPUTSERIAL
  #define DEBUGPRINT(...) {sprintf(bufferprint, __VA_ARGS__);Serial.print(bufferprint);}
#elif DEBUGOUTPUT == DEBUGOUTPUTTELNET
  #define DEBUGPRINT(...) {sprintf(bufferprint, __VA_ARGS__);sendTelnet(bufferprint);}
#else
  #define DEBUGPRINT(...)
#endif
