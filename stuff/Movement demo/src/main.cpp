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

    /*           IMU Calibration          */
    // set MPU_YAW_DRIFT equal to the average
    // sensors_event_t a, g, temp;
    // mpu.getEvent(&a, &g, &temp);
    // Serial.println(g.gyro.z);


    /*         Turning Calibration        */
    // set MPU_ANG_FIX so that the turns are perfect
    // test both -90 and 90
    // MPU_ANG_FIX is scaling, so it should be 0.7-1.3 at most
    turnAngle(-90);
    delay(500);
    turnAngle(-90);
    delay(500);
    turnAngle(-90);
    delay(500);
    turnAngle(-90);
    delay(500);
    turnAngle(90);
    delay(500);
    turnAngle(90);
    delay(500);
    turnAngle(90);
    delay(500);
    turnAngle(90);
    delay(500);



    /*         Encoder Calibration        */
    // set ENC_FIX_FRWD and ENC_FIX_BKWD so it goes mostly straight
    // change ENC_FIX_FRWD for forward movement (1000)
    // change ENC_FIX_BKWD for backward movement (-1000)
    // positive values increases power of left motor (turns more right)
    // moveForwardDist(enc1, 1000);



    /*         Line Sensor Debug        */
    // readLineSensor();
    // for(int i = 0; i < 13; i++) {
    //   Serial.print(lineArray[i]); Serial.print(" ");
    // }
    // Serial.println(" ");

// delay(500);

    /*            Turning Demo            */

    // turnCorner(enc1, true);     delay(750);
    // turnAngle(-90);             delay(750);
    // turnCorner(enc1, false);    delay(750);
    // turnAngle(270);             delay(750);
    // moveForwardDist(enc1, 75);  delay(750);
    // turnAngle(-180);            delay(750);
    // moveForwardDist(enc1, -75); delay(750);


    /*       Straignt line PID Demo       */
    
    // updateMoveForwardPID(true);
    // delay(10);


    /*           Line Follow Demo           */

    // updateLineFollow(0);
    // delay(10);

  }
}
