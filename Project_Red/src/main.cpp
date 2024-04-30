#include <Arduino.h>
#include <Adafruit_MCP3008.h>
#include <Adafruit_MPU6050.h>
#include <Encoder.h>

#include "movement.hpp"
#include "transition.hpp"

int state;

void setup() {
  Serial.begin(115200);

  movement_Init();

  M1_stop();
  M2_stop();

  state = 0;

  delay(100);
}


void loop() {
  Encoder enc1(M1_ENC_A, M1_ENC_B);
  Encoder enc2(M2_ENC_A, M2_ENC_B);
 
  delay(2000);

  if(state == 0) { // Line of the Republic
    transition = 0;

    do {
      updateLineFollow(enc1);
      delay(50);
    } while(transition == 0);
    
    transition_right();
    state = 1;


  } else if(state == 1) { // Maze of Mandalore
    transition = 0;

    // find maze entrance
    do {
      updateLineFollow(enc1);
      delay(50);
    } while(lineArray[12] == 0);
    
    turnAngle(-90);

    // skip maze
    int count = 0;
    do {
      updateMoveForwardPID(1);
      delay(50);
      count++;
    } while(count <= 60); //test

    turnAngle(90);

    // find line
    do {
      moveForwardDist(enc1, 10);
      readLineSensor();
    } while(lineArray[6] != 1);
    
    turnCorner(enc1, 0);

    do {
      updateLineFollow(enc1);
      delay(50);
    } while(transition == 0);

    transition_left();
    state = 2;


  } else if(state == 2) { // Kessel Run
    transition = 0;

    do {
      updateLineFollow(enc1);
      delay(50);
    } while(transition == 0);
    
    transition_left();
    state = 3;


  } else if(state == 3) { // Hoth Asteroid Field
    transition = 0;

    // get parallel to line
    turnAngle(90);
    moveForwardDist(enc1, 10);
    turnAngle(-90);

    // skip asteroid field
    int count = 0;
    do {
      updateMoveForwardPID(1);
      delay(50);
      count++;
    } while(count <= 100); //test
    
    turnAngle(-90);

    // find line
    do {
      moveForwardDist(enc1, 10);
      readLineSensor();
    } while(lineArray[6] != 1);
    
    turnAngle(90);

    do {
      updateLineFollow(enc1);
      delay(50);
    } while(transition == 0);

    transition_left();
    state = 4;


  } else if(state == 4) { // Path of Dual Fates
    transition = 0;

    do {
      updateLineFollow(enc1);
      delay(50);
    } while(transition == 0);
    
    transition_left();
    state = 5;


  } else if(state == 5) { // Second Line of the Republic
    transition = 0;
    do {
      updateLineFollow(enc1);
      delay(50);
    } while(transition == 0);
    
    transition_left();
    state = 6;


  } else if(state == 6) { // Endor Dash
    transition = 0;

    do {
      updateLineFollow(enc1);
      delay(50);
      readLineSensor();
    } while(lineArray[6] == 1);
    
    do {
      updateMoveForwardPID(1);
      delay(50);
      readLineSensor();
    } while(lineArray[6] == 0); //test

    moveForwardDist(enc1, 50);

    state = 7;
  } else { // Finish

  }  
}