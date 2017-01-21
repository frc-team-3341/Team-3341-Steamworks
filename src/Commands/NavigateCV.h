/*
 * NavigateCV.h
 *
 *  Created on: Jan 14, 2017
 *      Author: danie
 */


#ifndef SRC_NAVIGATECV_H_
#define SRC_NAVIGATECV_H_

#include <Utilities/WVPIDController.h>
#include <WPILib.h>
#include "../CommandBase.h"


using namespace frc;

class NavigateCV: public CommandBase{

private:
	// CV Changed
	bool cvChanged;

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

public:
	NavigateCV();
	void Execute();
	void Initialize();
	bool IsFinished();
	void End();
	void Interrupted();

	virtual ~NavigateCV();
};

#endif /* SRC_NAVIGATECV_H_ */
