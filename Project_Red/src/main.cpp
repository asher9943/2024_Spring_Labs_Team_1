#include <Arduino.h>
#include <Adafruit_MCP3008.h>
#include <Adafruit_MPU6050.h>
#include <Encoder.h>

#include "movement.hpp"
#include "transition.hpp"
#include "heltec_espnow.hpp"
#include "heltec_wifi.hpp"

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
 Serial.print("hi");

  delay(2000);
  
  // TODO wait for go from computer
  // moveForwardDist(enc1, 100);
  moveForwardDist(true, 100);

  while(true) {
    transition = 0;
    
    if(state == 0) { // Line of the Republic ---------------------------
      
      do {
        updateLineFollow(10);
        delay(10);
      } while(lineArray[12] == 0 && lineArray[0] == 0);
      M1_stop();
      M2_stop();
      delay(100);

      transition_right(enc1);
      state = 1;
      delay(100);
      // tell next robot to go?


    } else if(state == 1) { // Maze of Mandalore ----------------------
      
      // find maze entrance
      do {
        updateLineFollow(0);
        if(lineArray[0] != 0) break;
        delay(10);
      } while(lineArray[0] == 0);
      M1_stop();
      M2_stop();
      delay(100);

      // moveForwardDist(enc1, -100);
      moveForwardDist(false, 400);
      delay(100);

      // skip maze
      turnAngle(-115);

      int count = 0;
      moveForwardDist(true, 3000);
      delay(100);

      turnAngle(75);

      // find line again
      do {
        updateMoveForwardPID(true);
        delay(10);
        readLineSensor();
      } while(lineArray[6] != 1 || lineArray[7] != 1); //TODO test
      M1_stop();
      M2_stop();
      delay(100);
      // moveForwardDist(enc1, 50);
      moveForwardDist(true, 100);

      align(false);
      delay(100);

      // finish section
      do {
        updateLineFollow(0);
        delay(10);
      } while(lineArray[12] == 0 && lineArray[0] == 0);
      M1_stop();
      M2_stop();
      delay(100);

      transition_left(enc1);
      state = 2;
      delay(100);


    } else if(state == 2) { // Kessel Run -----------------------------

      do {
        updateLineFollow(-10);
        delay(10);
      } while(lineArray[12] == 0 || lineArray[0] == 0);
      M1_stop();
      M2_stop();
      delay(100);

      transition_left(enc1);
      state = 3;
      delay(100);


    } else if(state == 3) { // Hoth Asteroid Field ---------------------

      // get parallel to line
      turnAngle(90);
      delay(100);
      // moveForwardDist(enc1, 75);
      moveForwardDist(true, 100);
      delay(100);
      turnAngle(-90);
      delay(100);

      // skip asteroid field
      int count = 0;
      do {
        updateMoveForwardPID(true); //TODO wifi check
        delay(10);
        count++;
      } while(count <= 200); //TODO test
      M1_stop();
      M2_stop();
      delay(100);

      // find line again
      turnAngle(-90);
      delay(100);

      do {
        // moveForwardDist(enc1, 10); //TODO wifi check
        moveForwardDist(true, 100);
        readLineSensor();
      } while(lineArray[6] != 1);
      // moveForwardDist(enc1, 75);
      moveForwardDist(true, 100);
      delay(100);

      align(true);
      delay(100);

      // finish section
      do {
        updateLineFollow(0);
        delay(10);
      } while(lineArray[12] == 0 && lineArray[0] == 0);
      M1_stop();
      M2_stop();
      delay(100);

      transition_left(enc1);
      state = 4;
      delay(100);


    } else if(state == 4) { // Path of Dual Fates ---------------------

      // get in place
      do {
        updateLineFollow(10);
        delay(10);
      } while(lineArray[0] == 0);
      M1_stop();
      M2_stop();
      delay(100);

      turnCorner(enc1, false);
      delay(100);

      do {
        updateLineFollow(10);
        delay(10);
      } while(lineArray[12] == 0 && lineArray[0] == 0);
      M1_stop();
      M2_stop();
      delay(100);

      // tell computer to listen


      while(0); //wait for information

      // select direction
      if(1) {   // left
        turnCorner(enc1, true);
        delay(100);

        do {
          updateLineFollow(0); //TODO wifi check
          if(lineArray[0] == 1) turnCorner(enc1, false);
          delay(10);
        } while(lineArray[12] == 0);
        M1_stop();
        M2_stop();
        delay(100);

        turnCorner(enc1, true);
        delay(100);

      } else {  // right
        turnCorner(enc1, false);
        delay(100);

        do {
          updateLineFollow(0); //TODO wifi check
          if(lineArray[12] == 1) turnCorner(enc1, true);
          delay(10);
        } while(lineArray[0] == 0);
        M1_stop();
        M2_stop();
        delay(100);

        turnCorner(enc1, false);
        delay(100);
      }

      // follow line to end
      do {
        updateLineFollow(10);
        delay(10);
      } while(lineArray[12] == 0 && lineArray[0] == 0);
      M1_stop();
      M2_stop();
      delay(100);

      transition_left(enc1);
      state = 5;
      delay(100);


    } else if(state == 5) { // Second Line of the Republic ------------

      do {
        updateLineFollow(10);
        delay(10);
      } while(lineArray[12] == 0 && lineArray[0] == 0);
      M1_stop();
      M2_stop();
      delay(100);

      transition_left(enc1);
      state = 6;


    } else if(state == 6) { // Endor Dash ----------------------------

      do {
        updateLineFollow(10);
        delay(10);
      } while(lineArray[6] == 1);
      M1_stop();
      M2_stop();
      delay(100);

      do {
        updateMoveForwardPID(true); //TODO wifi check
        delay(10);
        readLineSensor();
      } while(lineArray[6] == 0);

      // moveForwardDist(enc1, 50);
      moveForwardDist(true, 100);

      state = 7;


    } else { // Finish -----------------------------------------------
      while(1) {
        turnAngle(90);
       //TODO wifi check
      }

    }
  }
}