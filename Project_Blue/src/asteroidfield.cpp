#include "asteroidfield.hpp"

//******************************************************************
//                          Functions
//******************************************************************

void move_around() {
    turnAngle(90);
    moveForwardDist(true, 160);
    turnAngle(-90);
    moveForwardDist(true, 240);
    turnAngle(-90);
    moveForwardDist(true, 160);
    turnAngle(90);
}