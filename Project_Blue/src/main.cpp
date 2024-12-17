#include <Arduino.h>
#include <Adafruit_MCP3008.h>
#include <Adafruit_MPU6050.h>
#include <Encoder.h>

#include "movement.hpp"
#include "transition.hpp"
#include "heltec_espnow.hpp"
#include "asteroidfield.hpp"
#include "maze.hpp"

int state;

void setup() {
  Serial.begin(115200);

  movement_Init();
  // heltec_espnow_Init();
  // wifi_Init();

  M1_stop();
  M2_stop();

  state = 0;

  delay(100);
}


void loop() {
  Encoder enc1(M1_ENC_A, M1_ENC_B);
  Encoder enc2(M2_ENC_A, M2_ENC_B);

  delay(2000);
  
  // TODO wait for go from computer

  while(true) {
    transition = 0;
    
    if(state == 0) { // Line of the Republic ---------------------------

      // go onto line
      do {
        updateMoveForwardPID(true);
        delay(10);
        readLineSensor();
      } while(lineArray[0] == 1 || lineArray[12] == 1);


      // line follow
      do {
        delay(10);
        updateLineFollow(10);
      } while(lineArray[12] == 0 && lineArray[0] == 0);
      M1_stop();
      M2_stop();
      delay(100);


      // transition
      transition_right(450);
      state = 1;
      delay(100);


    } else if(state == 1) { // Maze of Mandalore ----------------------
      
      // find maze entrance
      do {
        delay(10);
        updateLineFollow(-10);
      } while(lineArray[0] == 0 || lineArray[6] == 0);
      M1_stop();
      M2_stop();
      delay(100);

      // solve maze
      delay(5000);

    }
  }
}