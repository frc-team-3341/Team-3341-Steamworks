#include "SetDriveReverse.h"

SetDriveReverse::SetDriveReverse() {
	Requires(drive);
}

// Called just before this Command runs the first time
void SetDriveReverse::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SetDriveReverse::Execute() {
	drive->setMult(-1.0);
}

// Make this return true when this Command no longer needs to run execute()
bool SetDriveReverse::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SetDriveReverse::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetDriveReverse::Interrupted() {

}
