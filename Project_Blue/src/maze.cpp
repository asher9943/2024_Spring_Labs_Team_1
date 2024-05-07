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
 * Maze init
*/
void initMaze() {
    step = 0;
    prev_step = 0;
    pos_prev = LINE_MID;
}

/**
 * Navigates the maze for Blue Robot
*/
void navigateMaze() {
    prev_step = step;
    moveForwardDist(enc1, 130); // WIP Distance
    // Request image
    while(step == prev_step) {
        mazeLineFollow();
        delay(50);
    }
}

/**
 * Go around an obstacle
*/
void moveAround() {
    turnAngle(90);
    moveForwardDist(enc1,50); // WIP distance
    turnAngle(-90);
    moveForwardDist(enc1,50);
    turnAngle(90);
    moveForwardDist(enc1,50);
    turnAngle(-90);
}

/**
 * Modified line follow for maze solving
*/
void mazeLineFollow() {
    static float t_prev = millis();
    float pos;

    static float error = 0;
    static float prev_error = 0;

    float pid_val = 0;
    float Kp = 2.5;
    float Kd = 50;

    uint8_t intersection = 0;
  
    // too long between updates, reset PID
    if((millis() - t_prev) >= 500) {
        error = 0;
        prev_error = 0;
    }
    t_prev = millis(); 


    // update PID
    readLineSensor();

    pos = getLinePosition();
    error = pos - LINE_MID;

    pid_val = Kp*error + Kd*(error-prev_error);


    // apply PID
    M1_forward(PWM_BASE + pid_val);
    M2_forward(PWM_BASE - pid_val);


    // check for corner/intersection/ new section
    if((lineArray[0] == 1 || lineArray[12] == 1) && abs(prev_error) <= 4) {
        step++; 
    }


    // update "previous" values
    pos_prev = pos;
    prev_error = error;
}