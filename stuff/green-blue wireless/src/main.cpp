#include <Arduino.h>
#include "heltec_espnow.hpp"



void setup() {
  // stop right motor from running
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);

  Serial.begin(115200);

  heltec_espnow_Init();
}

void loop() {
  
}
