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
    
    moveForwardDist(true, 600);
    delay(100);
    turnAngle(-90);
    delay(100);
    moveForwardDist(true, 600);
}

/**
 * Transitions using a left turn
*/
void transition_left(Encoder enc1) {
    moveForwardDist(true, 600);
    delay(100);
    turnAngle(90);
    delay(100);
    moveForwardDist(true, 600);
}