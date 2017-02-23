/*


 * NewNavigateCV.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: Sauhaarda Chowdhuri + Daniel Ryu + Dhruti Pandya

*/

/*
#include "NewNavigateCV.h"
#include <iostream>
#include <math.h>

using namespace std;

NewNavigateCV::NewNavigateCV(){
	Requires(drive);

	state = 0;

	// Temporary initial values for Kp, Ki, and Kd.
	distKp = distKi = distKd = 1;
	angleKp = angleKi = angleKd = 1;

	// Set the goal distance and angle to 0. We are at this point right now so nothing will happen.
	distGoal = angleGoal = 0;
	leftDistance = 0;
	rightDistance = 0;



	angle = 0;
	power = 0;
	gyroVal = 0;
	distPID = 0;
	encoderVal = 0;
	anglePID = NULL;
	clock_initial = std::clock();
	clock_final = std::clock();
}
void NewNavigateCV::Initialize()
{

//	const int INITIAL_CV_WAIT = 0;
//	const int ANGLE_PID = 1;
//	const int DIST_PID = 2;
	state = 0;

	// Temporary initial values for Kp, Ki, and Kd.
	distKp = distKi = distKd = 1;
	angleKp = angleKi = angleKd = 1;

	// Set the goal distance and angle to 0. We are at this point right now so nothing will happen.
	distGoal = angleGoal = 0;
	leftDistance = 0;
	rightDistance = 0;

	angle = 0;
	power = 0;
	gyroVal = 0;
	distPID = 0;
	encoderVal = 0;
	anglePID = NULL;

	distPID = new WVPIDController(distKp, distKi, distKd, distGoal, false);
	anglePID = new WVPIDController(angleKp, angleKi, angleKd, angleGoal, false);

	drive->resetEncoders();
	drive->resetGyro();

	anglePID->SetSetPoint(0);
	distPID->SetSetPoint(0);
}

void NewNavigateCV::Execute()
{
	cout << "State:\t" << state << endl;
	if(state == WAIT_CV)
	{
		if(NetworkTablesInterface::gearFound()){
			angleGoal = -NetworkTablesInterface::getGearAzimuth();
			distGoal = NetworkTablesInterface::getGearDistance();

			cout << "Angle Goal:\t" << angleGoal << endl;
			cout << "Distance Goal:\t" << distGoal << endl;

			angle = anglePID->Tick(angleGoal);
			power = distPID->Tick(distGoal);

			cout << "Angle Tick:\t" << angle << endl;
			cout << "Distance Tick:\t" << power << endl;

			drive->arcadeDrive(power, angle);

			if(distGoal < 0.2)
			{
				state = FINISHED;
			}
			else
			{
				t_start = std::chrono::high_resolution_clock::now();
				state = MOVING;
				cout << "Transition from WAIT_CV to MOVING" << endl;
			}
		}
	}else if(state == MOVING){
		t_end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span;
		time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_start);
		if(time_span.count() > 1){ // every second
			drive->arcadeDrive(0, 0);
			state = WAIT_CV;
			cout << "Transition from MOVING to WAIT_CV" << endl;
		}
	}

#ifdef OLDCODE
	cout << "State:\t" << state << endl;
	if(state == INITIAL_CV_WAIT){ // wait for CV to find the gear
		t_end = std::chrono::high_resolution_clock::now();
		if((int)(time_span.count()) % 2 == 0 && NetworkTablesInterface::gearFound())
			state = ANGLE_PID;
		else if((int)(time_span.count()) % 2 == 1)
			drive->arcadeDrive(0,0);

	}else if(state == ANGLE_PID){
		angleGoal = -NetworkTablesInterface::getGearAzimuth();
		angle = anglePID->Tick(angleGoal);
		drive->arcadeDrive(0, angle);
		if(abs(angleGoal) < 1)
			state = DIST_CV_WAIT;
		state = INITIAL_CV_WAIT;
	}else if(state == DIST_CV_WAIT){ // check if gear is found
		if(NetworkTablesInterface::gearFound()) // check if gear is found
			state = DIST_PID;
	}else if(state == DIST_PID){
		if(distGoal != NetworkTablesInterface::getGearDistance()){
			distGoal = NetworkTablesInterface::getGearDistance();
			distPID->SetSetPoint(distGoal);
			drive->resetEncoders();
			if(abs(distGoal) < 0.2)
				state = FINISHED;
		}

		// Get Encoder Data
		leftDistance = drive->getLeftEncoderDistance();
		rightDistance = drive->getRightEncoderDistance();
		double encoderVal = ((abs(leftDistance)+abs(rightDistance))/2.0);

		// Tick and Drive
		power =  distPID->Tick(encoderVal * CLICKS_TO_METERS);
		drive->arcadeDrive(power, 0);
	}
#endif
}

bool NewNavigateCV::IsFinished(){
	return state == FINISHED;
}

void NewNavigateCV::End(){
	drive->arcadeDrive(0,0);
}

void NewNavigateCV::Interrupted(){
	// TODO: Put stuff here
}

NewNavigateCV::~NewNavigateCV(){
	delete distPID;
	delete anglePID;
}

*/
