#include "DriveToShoot.h"

DriveToShoot::DriveToShoot()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(drive);

		cvChanged = false;

			// Temporary initial values for Kp, Ki, and Kd.
		distKp = distKi = distKd = 1;
		angleKp = angleKi = angleKd = 1;

		// TODO: Set distance goal from testing
		distGoal = 0;
		angleGoal = 0;

		leftDistance = 0;
		rightDistance = 0;

		angle = 0;
		power = 0;
		gyroVal = 0;
		distPID = 0;
		encoderVal = 0;
		anglePID = NULL;
}

// Called just before this Command runs the first time
void DriveToShoot::Initialize()
{
	//Initialize cvChanged to false, signifying that CV has not yet changed their set point.
		/**cvChanged = false;

		// Temporary initial values for Kp, Ki, and Kd.
		distKp = distKi = distKd = 1;
		angleKp = angleKi = angleKd = 1;

		// Set the goal distance and angle to 0. We are at this point right now so nothing will happen.
		distGoal = angleGoal = 0;**/

		// Initialize both PIDs
		distPID = new WVPIDController(distKp, distKi, distKd, distGoal, false);
		anglePID = new WVPIDController(angleKp, angleKi, angleKd, angleGoal, false);

		drive->resetEncoders();
		drive->resetGyro();
}

// Called repeatedly when this Command is scheduled to run
void DriveToShoot::Execute()
{
/*	if(distGoal != NetworkTablesInterface::getGearDistance() || angleGoal != NetworkTablesInterface::getGearAzimuth())
		{
			cvChanged = true;
			distGoal = NetworkTablesInterface::getGearDistance();
			angleGoal = NetworkTablesInterface::getGearAzimuth();
			std::cout << "hi\n";
		}
		else
		{
			cvChanged = false;
		} */

		// TODO: Get dhruti on network tables for CVDistance

		leftDistance = drive->getLeftEncoderDistance();
		rightDistance = drive->getRightEncoderDistance();
		encoderVal =  distPID->Tick((abs(leftDistance)+abs(rightDistance))/2.0);
		gyroVal = drive->getGyroAngle();

		power = distPID->Tick(encoderVal);
		angle = anglePID->Tick(gyroVal);

		drive->arcadeDrive(power, angle);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveToShoot::IsFinished()
{
	const double epsilon = 0.1;
	return abs(distGoal - abs(CVDistance)) < epsilon;
}

// Called once after isFinished returns true
void DriveToShoot::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToShoot::Interrupted()
{

}
