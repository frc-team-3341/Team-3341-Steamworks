#include "SetDriveReverse.h"

SetDriveReverse::SetDriveReverse() {
	Requires(drive);
	Initialize();
	std::cout << "Current drive mult: " << drive->mult;
}

// Called just before this Command runs the first time
void SetDriveReverse::Initialize() {
	currentMult = drive->mult;
}

// Called repeatedly when this Command is scheduled to run
void SetDriveReverse::Execute() {
	drive->setMult(-currentMult);
}

// Make this return true when this Command no longer needs to run execute()
bool SetDriveReverse::IsFinished() {
	return drive->mult == -currentMult;
}

// Called once after isFinished returns true
void SetDriveReverse::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetDriveReverse::Interrupted() {

}
