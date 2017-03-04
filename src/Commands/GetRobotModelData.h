/*
 * GetRobotModelData.h
 *
 *  Created on: Jan 14, 2017
 *      Author: sauhaarda
 */

#ifndef SRC_GetRobotModelData_H_
#define SRC_GetRobotModelData_H_

#include <Utilities/WVPIDController.h>
#include "Utilities/NetworkTablesInterface.h"
#include <time.h>
#include <WPILib.h>
#include "../CommandBase.h"

using namespace frc;

class GetRobotModelData: public CommandBase
{

private:

	const double RUN_TIME = 5; // in seconds
	const double POWER = 0.5;

	enum State
	{
		MOVE, TURN, END
	};
	State state;

	clock_t start, end; // clocks for timing

	double encoderVal;
	double gyroVal;

	// Variables for storing each separate encoder value
	double leftDistance;
	double rightDistance;

public:
	GetRobotModelData();
	void Execute();
	void Initialize();bool IsFinished();
	void End();
	void Interrupted();

	virtual ~GetRobotModelData();
};

#endif /* SRC_GetRobotModelData_H_ */
