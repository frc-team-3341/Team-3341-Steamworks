/*
 * NewNavigateCV.h
 *
 *  Created on: Jan 14, 2017
 *      Author: danie
 */

/*
#ifndef SRC_NewNavigateCV_H_
#define SRC_NewNavigateCV_H_

#include <Utilities/WVPIDController.h>
#include "Utilities/NetworkTablesInterface.h"
#include <WPILib.h>
#include "../CommandBase.h"
#include <chrono>
#include <ctime>
#include <thread>


using namespace frc;

class NewNavigateCV: public CommandBase{

private:
	int state;

	const int WAIT_CV = 0;
	const int MOVING = 1;
	const int FINISHED = 2;

	// Constants for fine tuning PID
	double angleKp, angleKi, angleKd;
	double distKp, distKi, distKd;

	//The two goal values for the PID. We will get these values from CV.
	double angleGoal, distGoal;

	// PID Controller which controls power of the motor, and takes
	// sensor input of the encoder values and CV distance.
	WVPIDController* distPID;
	WVPIDController* anglePID;

	// Variable for storing the last average encoder value, and last gyro angle value respectively.
	double encoderVal, gyroVal;

	// Variables for storing each separate encoder value
	double leftDistance;
	double rightDistance;

	double power;
	double angle;
	std::clock_t clock_initial;
    std::chrono::high_resolution_clock::time_point t_start;

    std::clock_t clock_final;
    std::chrono::high_resolution_clock::time_point t_end;

public:
	NewNavigateCV();
	void Execute();
	void Initialize();
	bool IsFinished();
	void End();
	void Interrupted();

	virtual ~NewNavigateCV();
};

#endif /* SRC_NewNavigateCV_H_ */

