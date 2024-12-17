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
void transition_right(int forward) {
    
    moveForwardDist(true, forward);
    delay(100);
    turnAngle(-90);
    delay(100);
    moveForwardDist(true, 450);
}

/**
 * Transitions using a left turn
*/
void transition_left(int forward) {
    moveForwardDist(true, forward);
    delay(100);
    turnAngle(85);
    delay(100);
    moveForwardDist(true, 450);
}