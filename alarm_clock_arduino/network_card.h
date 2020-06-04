#include <WiFi101.h>

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

//WiFi adapter functions
//
//Prints details of currently connected AP
void printCurrentNet();

//Prints IP/MAC of WiFi adapter
void printWiFiData();
