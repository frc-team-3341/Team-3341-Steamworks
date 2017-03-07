#ifndef TURN_H
#define TURN_H

#include "../CommandBase.h"
#include "../Utilities/WVPIDController.h"
#include "WPILib.h"

class Turn : public CommandBase {
public:
	Turn(double inAngle);
	Turn(double* inAngle);
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
	void ForceFinish();

private:
	double angle;
	double* pAngle;
	bool forceFinish;
	bool pointerUsed;
	WVPIDController* anglePID;
};

#endif
