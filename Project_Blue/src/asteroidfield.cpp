#include "asteroidfield.hpp"

//******************************************************************
//                          Variables
//******************************************************************

//******************************************************************
//                          Functions
//******************************************************************

void move_around() {
    turnAngle(90);
    moveForwardDist(enc1, 160);
    turnAngle(-90);
    moveForwardDist(enc1, 240);
    turnAngle(-90);
    moveForwardDist(enc1, 160);
    turnAngle(90);
}