#include "Commands/Drive.h"

Drive::Drive(double inDistance, double inPower) :
		distance(inDistance * PIDCON_INCHES * 1.185){
	Requires(drive);
	distancePid = NULL;
	forceFinish = false;
	power = inPower;
}

void Drive::Initialize() {
	SetTimeout(20);
	drive->resetEncoders();
	drive->resetGyro();
	distancePid = new WVPIDController(0.15, 0.0, 0.0, distance, false);
}

void Drive::Execute() {
	double current_distance = drive->getDistance();
	double pwm_val = distancePid->Tick(current_distance);
	double current_angle = drive->getGyroAngle();

//	std::cout << "ERROR!!!!: " << distancePid->GetError() << std::endl;
//	std::cout << "pwm: " << pwm_val << std::endl;

	//std::cout << "Gyro PV: " << current_angle << std::endl;
	// std::cout << "Gyro error: " << anglePid->GetError() << std::endl;

	drive->arcadeDrive(DriveTrain::Limit(pwm_val, power), 0);
}

bool Drive::IsFinished() {
	bool finished = (((fabs(distancePid->GetError()) < 1)));
	if (finished)
		std::cout << "Drive finished" << std::endl;
	return finished || forceFinish || IsTimedOut();
}

void Drive::ForceFinish() {
	forceFinish = true;
}

void Drive::End() {
	drive->arcadeDrive(0, 0);
}

void Drive::Interrupted() {
}
