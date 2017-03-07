#ifndef DriveXFeet_H
#define DriveXFeet_H

#include "../CommandBase.h"
#include "../Utilities/WVPIDController.h"
#include "WPILib.h"

class Drive: public CommandBase {
public:
	Drive(double inDistance, double inPower);
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
	void ForceFinish();

private:
	double distance;
	double power;
	double angle;bool forceFinish;
	WVPIDController* distancePid;
};

#endif
