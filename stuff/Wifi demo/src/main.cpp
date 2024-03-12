#include <Arduino.h>

#include "heltec_wifi.hpp"


void setup() {
  // stop right motor from running
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);

  Serial.begin(115200);

  heltec_Wifi_Init();

  delay(100);
}


void loop(){
  process_client();
}

