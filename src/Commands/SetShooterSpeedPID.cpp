#include <Commands/SetShooterSpeedPID.h>

SetShooterSpeed::SetShooterSpeed()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(shooter);
	// TODO: figure out goalSpeed
	goalSpeed = 0;
	calculatedVal = 0;
	 _loops = 0;
	 _lastButton1 = false;
	 _talon->SetControlMode(CANSpeedController::kPercentVbus);
	 _talon->ConfigLimitMode(CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
		 // Use Requires() here to declare subsystem dependencies
		// eg. Requires(Robot::chassis.get());

}

// Called just before this Command runs the first time
void SetShooterSpeed::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void SetShooterSpeed::Execute()
{
	//encoderVal = shooter->getRate();
	calculatedVal = speedPID->Tick(encoderVal);
	shooter->setSpeed(calculatedVal);
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterSpeed::IsFinished()
{
	// TODO: figure out how to see when target speed has been reached
	return false;
}

// Called once after isFinished returns true
void SetShooterSpeed::End()
{
	shooter->~Shooter();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterSpeed::Interrupted()
{

}

double SetShooterSpeed::findSpeed(double dist)
{
	// some random physics madness
	// Target height and shooter angle are both constants
	double yComponent = sqrt(2 * 9.81 * TARGET_HEIGHT);
	return yComponent / sin(SHOOTER_ANGLE);
	//double xComponent = speed * cos(SHOOTER_ANGLE);
}
