#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <Adafruit_MCP3008.h>
#include <Adafruit_MPU6050.h>

#ifndef MOVEMENT_H_
#include "movement.hpp"
#endif

//******************************************************************
//                          Protoypes
//******************************************************************

/**
 * Transitions using a right turn
*/
void transition_right(Encoder enc1);
/**
 * Transitions using a left turn
*/
void transition_left(Encoder enc1);
#endif