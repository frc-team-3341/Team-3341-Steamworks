#include "Commands/Turn.h"

Turn::Turn(double inAngle) : angle(inAngle) {
	Requires(drive);
	anglePid = NULL;
	forceFinish = false;
}

void Turn::Initialize() {
	SetTimeout(5);
	drive->resetEncoders();
	drive->resetGyro();
	anglePid = new WVPIDController(0.15, 0, 0, angle, false); // kp was 0.1 before,works for low bar
}

void Turn::Execute() {
	double current_angle = drive->getGyroAngle();
	double rotateVal = anglePid->Tick(current_angle);

	std::cout << "curr_dist: " << current_angle << std::endl;

	//std::cout << "Gyro PV: " << current_angle << std::endl;
	// std::cout << "Gyro error: " << anglePid->GetError() << std::endl;

	drive->arcadeDrive(0, -DriveTrain::Limit(rotateVal, 0.4));
}

bool Turn::IsFinished() {
	bool finished = (fabs(anglePid->GetError()) < 1);

	if (finished)
		std::cout << "Autonomous finished" << std::endl;

	return finished || forceFinish || IsTimedOut();
}

void Turn::ForceFinish() {
	forceFinish = true;
}

void Turn::End() {
	drive->arcadeDrive(0, 0);
}

void Turn::Interrupted() {
}
