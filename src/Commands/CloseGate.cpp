#include "CloseGate.h"

CloseGate::CloseGate() {
	Requires(shooter);
}

// Called just before this Command runs the first time
void CloseGate::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void CloseGate::Execute() {
	shooter->setServo(0);
}

// Make this return true when this Command no longer needs to run execute()
bool CloseGate::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CloseGate::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CloseGate::Interrupted() {

}
