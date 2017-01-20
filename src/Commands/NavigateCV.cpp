/*
 * NavigateCV.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: Sauhaarda Chowdhuri + Daniel Ryu + Dhruti Padya
 */

#include "NavigateCV.h"

NavigateCV::NavigateCV()
{
//	TODO: Uncomment these lines when drive and gyro subsystems are implemented.
//	Requires(drive);
//	Requires(gyro);
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
}

void NavigateCV::Execute()
{

//	@dhruti TODO: Finish Network Tables Interface. Pseudocode is given below.
//	if(distGoal != networkTablesDistance || angleGoal != networkTablesAngle){
//		cvChanged = true;
//		distGoal = networkTablesDistance;
//		angleGoal = networkTablesAngle;
//	}else{
//		cvChanged = false;
//	}

	if(cvChanged)
	{
		//TODO: Reset drive encoders and gyro once subsystems are implemented.

		distPID->SetSetPoint(distGoal);
		anglePID->SetSetPoint(angleGoal);

	}


//	TODO: Uncomment and get real values once gyro and encoder sybsytems are implemented.
//	encoderVal = (drive->leftEncoderVal + drive->rightEncoderVal)/2.0d;
//	gyroVal = gyro->GetAngle();

	double power = distPID->Tick(encoderVal);
	double angle = anglePID->Tick(gyroVal);

//	TODO: Uncomment when arcade drive is implement.
//	arcadeDrive(power, angle);

}

bool NavigateCV::IsFinished()
{
	const double epsilon = 0.1;
	return (encoderVal - distGoal)*(encoderVal - distGoal) < epsilon &&
			(gyroVal - angleGoal)*(gyroVal - angleGoal) < epsilon;
}

void NavigateCV::End()
{

}

void NavigateCV::Interrupted()
{

}

NavigateCV::~NavigateCV()
{
	delete distPID;
	delete anglePID;
}
