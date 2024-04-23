#include <Arduino.h>
#include "heltec_wifi.hpp"
#include "heltec_espnow.hpp"

// #define TRANSMITER

void setup() {
  // stop right motor from running
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);

  Serial.begin(115200);

  heltec_espnow_Init();
  wifi_Init();

}

void loop() {
  
}
