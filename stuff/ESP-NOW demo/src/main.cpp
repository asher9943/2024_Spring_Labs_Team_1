#include <Arduino.h>
#include "heltec_espnow.hpp"


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
  strcpy(espMessageData.a, "HELLO");
  espMessageData.b = 5;
  espMessageData.c = 1.2;
  espMessageData.d = false;

  esp_err_t result = esp_now_send(donaldAddr, (uint8_t *) &espMessageData, sizeof(espMessageData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(2000);
}
