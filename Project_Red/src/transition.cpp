#include "transition.hpp"

//******************************************************************
//                          Variables
//******************************************************************

//******************************************************************
//                          Functions
//******************************************************************


/**
 * Transitions using a right turn
*/
void transition_right(Encoder enc1) {
    moveForwardDist(enc1, 80);
    delay(100);
    turnAngle(-90);
    delay(100);
    moveForwardDist(enc1, 152.4);
}

/**
 * Transitions using a left turn
*/
void transition_left(Encoder enc1) {
    moveForwardDist(enc1, 80);
    delay(100);
    turnAngle(90);
    delay(100);
    moveForwardDist(enc1, 152.4);
}