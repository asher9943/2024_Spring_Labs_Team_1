#include <Arduino.h>
#include "heltec_espnow.hpp"

// #define TRANSMITER

void setup() {
  // stop right motor from running
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);

  Serial.begin(115200);

  // get micromouse MAC address
  // Serial.println(WiFi.macAddress());

  heltec_espnow_Init();

}

void loop() {
  #ifdef TRANSMITER
  espMessageDataTx.maze_obsticle = 0;
  espMessageDataTx.dualFates_ready = 0;
  espMessageDataTx.dualFates_val = 0;
  espMessageDataTx.start = 0;
  espMessageDataTx.rescue = 0;

  esp_err_t result = esp_now_send(broadcaseAdd, (uint8_t *) &espMessageDataTx, sizeof(espMessageDataTx));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
  #endif
}
