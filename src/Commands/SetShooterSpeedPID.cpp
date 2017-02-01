#include <Commands/SetShooterSpeedPID.h>

SetShooterSpeed::SetShooterSpeed()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(shooter);

}

// Called just before this Command runs the first time
void SetShooterSpeed::Initialize()
{
	speedVal = 0;
	distance = 0;
	// figure out kp, ki, and kd through testing
	// setPoint is the speed we want the motors to run at so that the ball scores
	// TODO: figure out setPoint
	speedPID = new WVPIDController(0, 0, 0, SETPOINT, false);
	shooter->resetEncoder;
}

// Called repeatedly when this Command is scheduled to run
void SetShooterSpeed::Execute()
{
	// Network table stuff for getting distance and altitude
	/*
	if(NetworkTablesInterface::targetFound()){
	distance = NetworkTablesInterface::getDistance();
			 */
	currentSpeed = shooter->getRate();
	speedVal = findSpeed(distance);
	measuredSpeed = speedPID->Tick(speedVal);
	shooter->setSpeed(measuredSpeed);


	// TODO: Set motor to the speed PID

}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterSpeed::IsFinished()
{
	// TODO: figure out how to see when target speed has been reached
	return 0.01 < SETPOINT;
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
