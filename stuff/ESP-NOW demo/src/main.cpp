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
  strcpy(espMessageDataTx.a, "HELLO");
  espMessageDataTx.b = 5;
  espMessageDataTx.c = 1.2;espMessageData
  espMessageDataTx.d = false;

  esp_err_t result = esp_now_send(broadcastAddr, (uint8_t *) &espMessageDataTx, sizeof(espMessageDataTx));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
  #endif
}
