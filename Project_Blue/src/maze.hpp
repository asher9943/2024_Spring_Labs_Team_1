#ifndef MAZE_H_
#define MAZE_H_

#include <Adafruit_MCP3008.h>
#include <Adafruit_MPU6050.h>
#include <Encoder.h>

#ifndef MOVEMENT_H_
#include "movement.hpp"
#endif

/******************************************************************
 *                          Protoypes
 ******************************************************************
 */

void initMaze();
void navigateMaze();

#endif