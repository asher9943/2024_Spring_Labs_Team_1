#include <Arduino.h>
#include <Adafruit_MCP3008.h>
#include <Adafruit_MPU6050.h>
#include <Encoder.h>

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
    
    /*            Turning Demo            */

    // turnCorner(enc1, true);     delay(750);
    // turnAngle(-90);             delay(750);
    // turnCorner(enc1, false);    delay(750);
    // turnAngle(270);             delay(750);
    // moveForwardDist(enc1, 75);  delay(750);
    // turnAngle(-180);            delay(750);
    // moveForwardDist(enc1, -75); delay(750);


    /*       Straignt line PID Demo       */

    // for(int i = 0; i < 1000; i++) {
    //   updateMoveForwardPID(true);
    // }
    // M1_stop();
    // M2_stop();
    // delay(1000);
    // for(int i = 0; i < 1000; i++) {
    //   updateMoveForwardPID(false); 
    // }
    // M1_stop();
    // M2_stop();
    // delay(1000);


    /*           Line Follow Demo           */

    // lineFollow(enc1);
    // delay(50);

  }
}
