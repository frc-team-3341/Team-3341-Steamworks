#ifndef SetShooterSpeed_H
#define SetShooterSpeed_H

#include "../CommandBase.h"
#include "OI.h"
#include "../Subsystems/Shooter.h"
#include "../Utilities/WVPIDController.h"
#include "CANTalon.h"

using namespace frc;

class SetShooterSpeed: public CommandBase
{
public:
	SetShooterSpeed();
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
	double findSpeed(double dist);

private:
	//CANTalon* _talon;
	//std::string _sb;
	int _loops;
	//bool _lastButton1;
	/** save the target position to servo to */
	//double targetPositionRotations;
	double currentSpeed;
	double correctionValue;
	double moveValue;
	double errorValue;
	double calculatedVal;
	double encoderVal;
	double goalSpeed;
	//TODO why do we need this button here?
	//The button should be instantiated in OI
	//with this command.- Nir
	//Button* shooterButton;
	WVPIDController* speedPID;
	// LiveWindow* lw;
};

#endif  // SetShooterSpeed_H

