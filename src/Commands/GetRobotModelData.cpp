/*
 * GetRobotModelData.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: Sauhaarda Chowdhuri
 */

#include "GetRobotModelData.h"
#include <time.h>

using namespace std;

GetRobotModelData::GetRobotModelData() {
	Requires(drive);
	Initialize();
}
void GetRobotModelData::Initialize() {
	state = MOVE;

	leftDistance = 0;
	rightDistance = 0;
	encoderVal = 0;

	drive->resetEncoders();
	drive->resetGyro();

	drive->resetEncoders();
	drive->resetGyro();

	start = clock();
	cout << "Encoder Data:" << endl;
}

void GetRobotModelData::Execute() {
	end = clock();
	if (state == MOVE) {
		if (double(end - start) > RUN_TIME) {
			state = TURN;
			cout << "Gyro Data:" << endl;
			start = clock();
		} else {
			// Get Encoder Data
			leftDistance = drive->getLeftEncoderDistance();
			rightDistance = drive->getRightEncoderDistance();
			drive->arcadeDrive(POWER, 0);
			cout << (leftDistance + rightDistance) / 2.0 << endl; // Print encoder value
		}
	} else if (state == TURN) {
		if (double(end - start) > RUN_TIME) {
			state = END;
			drive->arcadeDrive(0, 0);
		} else {
			gyroVal = drive->getGyroAngle();
			drive->arcadeDrive(0, POWER);
			cout << gyroVal << endl;
		}
	}
}

bool GetRobotModelData::IsFinished() {
	return state == END;
}

void GetRobotModelData::End() {
	drive->arcadeDrive(0, 0);
}

void GetRobotModelData::Interrupted() {
	drive->arcadeDrive(0, 0);
}

GetRobotModelData::~GetRobotModelData() {
}
