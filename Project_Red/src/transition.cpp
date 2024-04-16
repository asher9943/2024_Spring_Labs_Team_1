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
void transition_right() {
    moveForwardDist(enc1, 152.4);
    turnAngle(90);
    moveForwardDist(enc1, 152.4);
}

/**
 * Transitions using a left turn
*/
void transition_left() {
    moveForwardDist(enc1, 152.4);
    turnAngle(-90);
    moveForwardDist(enc1, 152.4);
}