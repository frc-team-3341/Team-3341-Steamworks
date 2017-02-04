#include <Commands/SetShooterSpeedPID.h>

SetShooterSpeed::SetShooterSpeed()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(shooter);
	encoderVal = 0;
	// TODO: figure out goalSpeed
	goalSpeed = 0;
	calculatedVal = 0;
}

// Called just before this Command runs the first time
void SetShooterSpeed::Initialize()
{

	// figure out kp, ki, and kd through testing
	// setPoint is the speed we want the motors to run at so that the ball scores

	speedPID = new WVPIDController(0, 0, 0, goalSpeed, false);
	shooter->resetEncoder();
	// lw = LiveWindow::GetInstance(); TODO: figure out when i need to use this
}

// Called repeatedly when this Command is scheduled to run
void SetShooterSpeed::Execute()
{
	encoderVal = shooter->getRate();
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
