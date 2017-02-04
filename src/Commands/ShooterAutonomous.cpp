#include "ShooterAutonomous.h"

ShooterAutonomous::ShooterAutonomous() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(shooter);

		distance = 0;
		//azimuth = 0;
		speed = 0;
		altitude = 0;
		//speedPid = NULL
}

// Called just before this Command runs the first time
void ShooterAutonomous::Initialize() {

	if(NetworkTablesInterface::boilerFound()){
		distance = NetworkTablesInterface::getBoilerDistance();
		//azimuth = NetworkTablesInterface::GetAzimuth();
		altitude = NetworkTablesInterface::getBoilerAltitude();
	}
	else{
		distance = 0;
		altitude = 0;
	}
	//shooter->resetEncoder();
		//speed = shooter->getRate();
		//speedPid = new WVPIDController(0.5,0,0,findSpeed(distance), false);
		//shooter->resetAngle();
	}

// Called repeatedly when this Command is scheduled to run
void ShooterAutonomous::Execute() {
	//double current_rate = shooter->getRate();
		//double pwm_val = speedPid->Tick(current_rate);
		double speedVal = findSpeed(distance);
		shooter->setSpeed(speedVal);
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterAutonomous::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ShooterAutonomous::End() {

	shooter->loadBall();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterAutonomous::Interrupted() {

}
double ShooterAutonomous::findSpeed(double dist){


	double yComponent = sqrt(2 * 9.81 * TARGET_HEIGHT);
	return yComponent / sin(SHOOTER_ANGLE);
	//double xComponent = speed * cos(SHOOTER_ANGLE);

}
