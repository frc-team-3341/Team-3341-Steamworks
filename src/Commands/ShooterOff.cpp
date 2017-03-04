#include "ShooterOff.h"

ShooterOff::ShooterOff()
{
	Requires(shooter);
}

// Called just before this Command runs the first time
void ShooterOff::Initialize()
{
	shooter->setSpeed(0);
}

// Called repeatedly when this Command is scheduled to run
void ShooterOff::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool ShooterOff::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ShooterOff::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterOff::Interrupted()
{

}
