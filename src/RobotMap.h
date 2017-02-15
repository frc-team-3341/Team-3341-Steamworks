#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
//const int LEFTMOTOR = 1;
//const int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
//const int RANGE_FINDER_PORT = 1;
//const int RANGE_FINDER_MODULE = 1;

//const int MOTORPORT = 0;
const int WINCH_ENCODER1 = 40;
const int WINCH_ENCODER2 = 41;
const int WINCH_MOTOR = 43;
const double SHOOTER_ANGLE = 33;//set this to the constant angle
const double TARGET_HEIGHT = 7;//whatever the height is
const double ENCODER_RIGHT_1=0;
const double ENCODER_RIGHT_2=1;
const double ENCODER_LEFT_1=2;
const double ENCODER_LEFT_2=3;
const double LEFTSHOOTER= 4;
const double RIGHTSHOOTER= 5;
const double SHOOTERENCODERLEFT= 6;
const double SHOOTERENCODERRIGHT= 7;
const double PIDCON_INCHES = 0.13617;//inches


#endif
