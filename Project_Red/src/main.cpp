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
  heltec_espnow_Init();
  wifi_Init();

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

  if(state == 0) { // Line of the Republic ---------------------------
    transition = 0;

    do {
      updateLineFollow(enc1);
      delay(50);
    } while(transition == 0);
    
    transition_right();
    state = 1;
    // tell next robot to go?


  } else if(state == 1) { // Maze of Mandalore ----------------------
    transition = 0;

    // find maze entrance
    do {
      updateLineFollow(enc1);
      delay(50);
    } while(lineArray[12] == 0);
    
    // skip maze
    turnAngle(-90);

    int count = 0;
    do {
      updateMoveForwardPID(1);
      delay(50);
      count++;
    } while(count <= 60); //TODO test

    turnAngle(90);

    // find line again
    do {
      moveForwardDist(enc1, 10);
      readLineSensor();
    } while(lineArray[6] != 1);
    
    turnCorner(enc1, 0);

    // finish section
    do {
      updateLineFollow(enc1);
      delay(50);
    } while(transition == 0);

    transition_left();
    state = 2;


  } else if(state == 2) { // Kessel Run -----------------------------
    transition = 0;

    do {
      updateLineFollow(enc1); //TODO wifi check
      delay(50);
    } while(transition == 0);
    
    transition_left();
    state = 3;


  } else if(state == 3) { // Hoth Asteroid Field ---------------------
    transition = 0;

    // get parallel to line
    turnAngle(90);
    moveForwardDist(enc1, 10);
    turnAngle(-90);

    // skip asteroid field
    int count = 0;
    do {
      updateMoveForwardPID(1); //TODO wifi check
      delay(50);
      count++;
    } while(count <= 100); //TODO test
    
    // find line again
    turnAngle(-90);
    
    do {
      moveForwardDist(enc1, 10); //TODO wifi check
      readLineSensor();
    } while(lineArray[6] != 1);
    
    turnCorner(enc1, 1);

    // finish section
    do {
      updateLineFollow(enc1); //TODO wifi check
      delay(50);
    } while(transition == 0);

    transition_left();
    state = 4;


  } else if(state == 4) { // Path720 of Dual Fates ---------------------
    transition = 0;

    do {
      updateLineFollow(enc1); //TODO wifi check
      delay(50);
    } while(!(lineArray[0] == 1 && lineArray[12] == 1));
    
    // tell computer to listen


    while(0); //wait for information

    // select direction
    if(1) {   // left
      turnCorner(enc1, 1);

      do {
        updateLineFollow(enc1); //TODO wifi check
        delay(50);
      } while(lineArray[12] == 0);

      turnCorner(enc1, 1);

    } else {  // right
      turnCorner(enc1, 0);

      do {
        updateLineFollow(enc1); //TODO wifi check
        delay(50);
      } while(lineArray[0] == 0);

      turnCorner(enc1, 0);

    }
    
    // follow line to end
    do {
      updateLineFollow(enc1); //TODO wifi check
      delay(50);
    } while(transition == 0);

    transition_left();
    state = 5;


  } else if(state == 5) { // Second Line of the Republic ------------
    transition = 0;

    do {
      updateLineFollow(enc1); //TODO wifi check
      delay(50);
    } while(transition == 0);
    
    transition_left();
    state = 6;


  } else if(state == 6) { // Endor Dash ----------------------------
    transition = 0;

    do {
      updateLineFollow(enc1); //TODO wifi check
      delay(50);
      readLineSensor();
    } while(lineArray[6] == 1);
    
    do {
      updateMoveForwardPID(1); //TODO wifi check
      delay(50);
      readLineSensor();
    } while(lineArray[6] == 0);

    moveForwardDist(enc1, 50);

    state = 7;


  } else { // Finish -----------------------------------------------
    while(1) {
      turnAngle(45);
     //TODO wifi check
    }
    
  }  
}