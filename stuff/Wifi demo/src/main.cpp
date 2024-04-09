#include <Arduino.h>

#include "heltec_wifi.hpp"


void setup() {
  // stop right motor from running
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);

  Serial.begin(115200);

  wifi_Init();
  server_Init();

  delay(100);
}


void loop(){
  String client_rx_buff = "";
  String client_tx_buff = "";

  /*               Echo Demo               */

  if(client_check()) {
    // if there is data to receive
    if(client_read(&client_rx_buff)) {
      Serial.print(" - Recieved: ");
      Serial.println(client_rx_buff);

      client_tx_buff = client_rx_buff;

      client_write(client_tx_buff);

      Serial.print(" - Sent:     ");
      Serial.println(client_tx_buff);

      client_tx_buff = "";
    }
  }

  delay(50);
}

