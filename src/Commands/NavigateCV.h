/*
 * NavigateCV.h
 *
 *  Created on: Jan 14, 2017
 *      Author: sauhaarda
 */

#ifndef SRC_NAVIGATECV_H_
#define SRC_NAVIGATECV_H_

#include <Utilities/WVPIDController.h>
#include "Utilities/NetworkTablesInterface.h"
#include <time.h>
#include <WPILib.h>
#include "../CommandBase.h"

using namespace frc;

class NavigateCV: public CommandBase
{

private:

	const double IIR_CONST = 0.5;
	const double DRIVE_TIME = 1;

	enum State
	{
		CV, INNER_LOOP, END
	};
	State state;

	clock_t start, end; // clocks for timing

	// Constants for fine tuning PID
	double angleKp, angleKi, angleKd;
	double distKp, distKi, distKd;

	//The two goal values for the PID. We will get these values from CV.
	double angleGoal, distGoal;

	// PID Controller which controls power of the motor, and takes
	// sensor input of the encoder values and CV distance.
	WVPIDController* distPID;
	WVPIDController* anglePID;

	double encoderVal;
	double lastGyroVal, newGyroVal;

	// Variables for storing each separate encoder value
	double leftDistance;
	double rightDistance;

	double power;
	double angle;

public:
	NavigateCV();
	void Execute();
	void Initialize();bool IsFinished();
	void End();
	void Interrupted();

	virtual ~NavigateCV();
};

#endif /* SRC_NAVIGATECV_H_ */
