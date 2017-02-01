#ifndef SetShooterSpeed_H
#define SetShooterSpeed_H

#include "../CommandBase.h"

class SetShooterSpeed : public CommandBase
{
public:
	SetShooterSpeed();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double findSpeed(double dist);

private:
	double measuredSpeed;
	double currentSpeed;
	double speedVal;
	double distance;
	WVPIDController* speedPID;
};

#endif  // SetShooterSpeed_H
