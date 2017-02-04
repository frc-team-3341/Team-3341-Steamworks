#ifndef SetShooterSpeed_H
#define SetShooterSpeed_H

#include "../CommandBase.h"
#include "../Subsystems/Shooter.h"
#include "../Utilities/WVPIDController.h"

using namespace frc;

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
	double calculatedVal;
	double encoderVal;
	double goalSpeed;
	WVPIDController* speedPID;
	Shooter* shooter;
	// LiveWindow* lw;
};

#endif  // SetShooterSpeed_H
