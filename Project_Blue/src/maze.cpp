#include "maze.hpp"

/******************************************************************
 *                          Variables
 ******************************************************************
 */

float pos_prev;
int step;
int prev_step;

/******************************************************************
 *                          Functions
 ******************************************************************
 */

/**
 * Go around an obstacle
*/
void moveAround() {
    turnAngle(90);
    moveForwardDist(true,500); // WIP distance
    turnAngle(-90);
    moveForwardDist(true,500);
    turnAngle(90);
    moveForwardDist(true,500);
    turnAngle(-90);
    step++;
}

/**
 * Modified line follow for maze solving
*/
void mazeLineFollow(int boost) {
  static float t_prev = millis();
  float pos;

  static float error = 0;
  static float prev_error = 0;
  // static float total_error = 0;

  float pid_val = 0;
  float Kp = 5;
  float Kd = 25;
  // float Ki = 0.015;

  uint8_t intersection = 0;
  
  // too long between updates, reset PID
  if((millis() - t_prev) >= 100) {
    error = 0;
    prev_error = 0;
    //total_error = 0;
  }
  t_prev = millis(); 


  // update PID
  readLineSensor();

  pos = getLinePosition();
  error = pos - LINE_MID;
  // total_error += error;

  pid_val = Kp*error + Kd*(error-prev_error);
  // pid_val = Kp*error + Kd*(error-prev_error) + Ki*total_error;


  // apply PID
  M1_forward(PWM_BASE + boost - pid_val);
  M2_forward(PWM_BASE + boost + pid_val);

  if((lineArray[0] == 1 || lineArray[12] == 1) && abs(prev_error) <= 4) {
    step++;
  }

  // update "previous" values
  pos_prev = pos;
  prev_error = error;
}

/**
 * Navigates the maze for Blue Robot
*/
void navigateMaze() {
    prev_step = step;
    moveForwardDist(true, 500);
    // Request image
    while(step == prev_step) {
        mazeLineFollow(-10);
        delay(50);
    }
    if(step == 6 || step == 7 || step == 15) {
        moveForwardDist(true, 250);
        align(false);
    } else if(step == 11 || step == 12) {
        moveForwardDist(true,250);
        align(true);
    } else if(step == 16) {
        transition = 1;
    }
}

/**
 * Maze init
*/
void initMaze() {
    step = 0;
    prev_step = 0;
    pos_prev = LINE_MID;
}