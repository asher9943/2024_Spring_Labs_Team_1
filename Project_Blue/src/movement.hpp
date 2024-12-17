#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <Adafruit_MCP3008.h>
#include <Adafruit_MPU6050.h>
#include <Encoder.h>


/******************************************************************
 *                          Variables
 ******************************************************************
 */


// Motors
extern const unsigned int PWM_BASE; // Base PWM for motors
extern const unsigned int PWM_MAX;  // Max PWM for motors
extern const unsigned int PWM_MIN;  // Min PWM for motor movement


// Line sensor
extern Adafruit_MCP3008 adc1;
extern Adafruit_MCP3008 adc2;
extern uint8_t lineArray[];     // Line sensor data array
extern const float LINE_MID;    // Middle position of line sensor


// MPU
extern Adafruit_MPU6050 mpu;


// Encoders
extern const unsigned int M1_ENC_A;
extern const unsigned int M1_ENC_B;
extern const unsigned int M2_ENC_A;
extern const unsigned int M2_ENC_B;


// Transition Variable
extern int transition;


/* To use the encoders:

Insert the following into setup():
void setup() {
  //...
  movement_Init();
  //...

  M1_stop();
  M2_stop();

  delay(100);
}


Replace loop() with the following:
void loop() {
  Encoder enc1(M1_ENC_A, M1_ENC_B);
  Encoder enc2(M2_ENC_A, M2_ENC_B);
 
  while(true) {
    //...
  }
}

*/



/******************************************************************
 *                          Protoypes
 ******************************************************************
 */


// Movement initialization, put in setup()
void movement_Init();


// Basic motor control functions (M1 is left, M2 is right)
void M1_forward(int pwm_value);
void M2_forward(int pwm_value);
void M1_backward(int pwm_value);
void M2_backward(int pwm_value);
void M1_stop();
void M2_stop();


// Line sensor functions

/* 
 * Read line sensor data to find which sensors see white
 */
void readLineSensor();

/* 
 * Using line sensor data, find position of mouse on line
 * 
 * return
 *   pos - Current position of mouse on line
 */
float getLinePosition();


// MPU functions

/* 
 * Update current angle based on MPU values
 *   *curr_angle - Current angle the mouse is facing
 *   *g_prev     - Previous g.gyro.z value; updated in function
 *   *t_prev     - Previous millis() value; updated in function
 * 
 * If you do not yet have values for these paramters, use default:
 *   *curr_angle = 0
 *   *g_prev     = 0
 *   *t_prev     = millis()
 */
void updateAngle(float *curr_angle, float *g_prev, unsigned long *t_prev);


// Movement functions

/*
 *  Moves the mouse forward (or backward) by a certain amount
 *    enc1 - Pointer to encoder 1 (can also be enc2)
 *    goal_mm - Amount to move forward (mm)
 *      goal_mm > 0 - Move forward
 *      goal_mm < 0 - Move backward
 */
void moveForwardDist(bool forward, float goal_ms);

/*
 *  Turns the mouse by a specified amount
 *    goal - Amount to turn (degrees)
 *      goal > 0 - Counter clock-wise
 *      goal < 0 - Clock-wise
 */
void turnAngle(float goal);

/*
 *  Turns a corner using encoders and the IMU
 *    enc1 - Pointer to encoder 1 (can also be enc2)
 *    ccw  - If true, turns the mouse counter clock-wise
 */
void turnCorner(Encoder enc1, bool ccw);


/*
 *  Moves the mouse forward (or backward) using IMU for PID
 *    forward - If true mouse moves forward, else it moves backward
 */
void updateMoveForwardPID(bool forward);

/*
 *  Follows a line, function updates the lineFollow PID
 *    enc1 - Pointer to encoder 1 (in reality, can also be enc2)
 */
void updateLineFollow(int boost);

/*
 *  Follows a line, accounts for intersections
 *    enc1 - Pointer to encoder 1 (in reality, can also be enc2)
 */
void updateLineFollowInter(Encoder enc1);

/*  
 *  Detect the type of intersection the mouse is at
 * 
 *  return
 *    0 - New section
 *    1 - Left turn
 *    2 - Right turn
 *    3 -  T  intersection
 *    4 - -|  intersection
 *    5 -  |- intersection
 *    6 - -|- intersection
 */
int intersectionDetect(Encoder enc1);

#endif
