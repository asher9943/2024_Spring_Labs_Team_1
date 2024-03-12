#include <Arduino.h>

#include "movement.hpp"


void setup() {
  Serial.begin(115200);

  movement_Init();

  M1_stop();
  M2_stop();

  delay(100);
}


void loop() {
  Encoder enc1(M1_ENC_A, M1_ENC_B);
  Encoder enc2(M2_ENC_A, M2_ENC_B);
 
  delay(2000);

  while(true) {
    // turnCorner(enc1, true);   delay(750);
    // turnAngle(-90);           delay(750);
    // turnCorner(enc1, false);  delay(750);
    // turnAngle(270);           delay(750);
    // moveForward(enc1, 75);    delay(750);
    // turnAngle(-180);          delay(750);
    // moveForward(enc1, -75);   delay(750);

    // moveForward(enc1, 10000); delay(5000);

    lineFollow(enc1);

    Serial.println();
  }
}
