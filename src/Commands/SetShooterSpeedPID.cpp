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
	goalSpeed = -10259; //2130
	shooter->setPIDConstants(1,1,0,0);

}

// Called repeatedly when this Command is scheduled to run
void SetShooterSpeed::Execute()
{
	shooter->setSpeed(goalSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterSpeed::IsFinished()
{
	if(shooterButton)
	{
		return true;
	}
	return false;
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



