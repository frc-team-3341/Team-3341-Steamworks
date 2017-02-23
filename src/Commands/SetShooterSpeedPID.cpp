#include "Commands/SetShooterSpeedPID.h"

SetShooterSpeed::SetShooterSpeed()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(shooter);

		 // Use Requires() here to declare subsystem dependencies
		// eg. Requires(Robot::chassis.get());

}

// Called just before this Command runs the first time
void SetShooterSpeed::Initialize()
{
	// TODO: figure out goalSpeed
	goalSpeed = -15000; //2130
	shooter->setPIDConstants(1,1,0,0);

}


// Called repeatedly when this Command is scheduled to run
void SetShooterSpeed::Execute()
{
	shooter->setSpeed(goalSpeed);
	//std::cout << "Shooter Error: " << shooter->getError() << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterSpeed::IsFinished()
{
	return false; //may be return true but not sure
	}

// Called once after isFinished returns true
void SetShooterSpeed::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterSpeed::Interrupted()
{

}
