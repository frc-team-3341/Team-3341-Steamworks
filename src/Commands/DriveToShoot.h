#ifndef DriveToShoot_H
#define DriveToShoot_H

#include "../CommandBase.h"
#include "../Utilities/WVPIDController.h"

class DriveToShoot : public CommandBase {

private:
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

	double CVDistance;

public:
	DriveToShoot();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

};

#endif  // DriveToShoot_H



