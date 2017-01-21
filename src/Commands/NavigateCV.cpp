/*
 * NavigateCV.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: Sauhaarda Chowdhuri + Daniel Ryu + Dhruti Padya
 */

#include "NavigateCV.h"

NavigateCV::NavigateCV(){
	Requires(drive);
}
void NavigateCV::Initialize()
{
	//Initialize cvChanged to false, signifying that CV has not yet changed their set point.
	cvChanged = false;

	// Temporary initial values for Kp, Ki, and Kd.
	distKp = distKi = distKd = 1;
	angleKp = angleKi = angleKd = 1;

	// Set the goal distance and angle to 0. We are at this point right now so nothing will happen.
	distGoal = angleGoal = 0;

	// Initialize both PIDs
	distPID = new WVPIDController(distKp, distKi, distKd, distGoal, false);
	anglePID = new WVPIDController(angleKp, angleKi, angleKd, angleGoal, false);

	drive->resetEncoders();
	drive->resetGyro();

}

void NavigateCV::Execute(){


	if(distGoal != NetworkTablesInterface::getGearDistance() || angleGoal != NetworkTablesInterface::getGearAzimuth())
	{
		cvChanged = true;
		distGoal = NetworkTablesInterface::getGearDistance();
		angleGoal = NetworkTablesInterface::getGearAzimuth();
		std::cout << "hi\n";
	}
	else
	{
		cvChanged = false;
	}

	if(cvChanged)
	{
		drive->resetGyro();
		drive->resetEncoders();
		distPID->SetSetPoint(distGoal);
		anglePID->SetSetPoint(angleGoal);
	}

	leftDistance = drive->getLeftEncoderDistance();
	rightDistance = drive->getRightEncoderDistance();
	encoderVal =  distPID->Tick((abs(leftDistance)+abs(rightDistance))/2.0);
	gyroVal = drive->getGyroAngle();

	power = distPID->Tick(encoderVal);
	angle = anglePID->Tick(gyroVal);

	drive->arcadeDrive(power, angle);

}

bool NavigateCV::IsFinished()
{
	const double epsilon = 0.1;
	return (encoderVal - distGoal)*(encoderVal - distGoal) < epsilon &&
			(gyroVal - angleGoal)*(gyroVal - angleGoal) < epsilon;
}

void NavigateCV::End()
{
	// TODO: STOP THE MOTORS!!!!
	drive->arcadeDrive(0,0);
}

void NavigateCV::Interrupted()
{
	// TODO: Put stuff here
}

NavigateCV::~NavigateCV()
{
	delete distPID;
	delete anglePID;
}
