#include "Commands/Turn.h"

Turn::Turn(double inAngle) : angle(inAngle) {
	Requires(drive);
	anglePID = NULL;
	forceFinish = false;
	pointerUsed = false;
	Initialize();
}

Turn::Turn(double* inAngle) : pAngle(inAngle) {
	Requires(drive);
	anglePID = NULL;
	forceFinish = false;
	pointerUsed = true;
	Initialize();
}

void Turn::Initialize() {
	SetTimeout(5);
	if(pointerUsed)
		angle = *pAngle;
	std::cout << "Angle Set point:\t" << angle << std::endl;
	drive->resetEncoders();
	drive->resetGyro();
	anglePID = new WVPIDController(0.15, 0, 0, angle, false); // kp was 0.1 before,works for low bar
}

void Turn::Execute() {
	double current_angle = -drive->getGyroAngle();
	double rotateVal = anglePID->Tick(current_angle);

	std::cout << "gyro angle: " << current_angle << std::endl;
	std::cout << "pid response: " << rotateVal << std::endl;
	std::cout << "current error: " << anglePID->GetError() << std::endl;

	//std::cout << "Gyro PV: " << current_angle << std::endl;
	// std::cout << "Gyro error: " << anglePid->GetError() << std::endl;

	drive->arcadeDrive(0, -DriveTrain::Limit(rotateVal, 0.5));
}

bool Turn::IsFinished() {
	bool finished = (fabs(anglePID->GetError()) < 1);

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
