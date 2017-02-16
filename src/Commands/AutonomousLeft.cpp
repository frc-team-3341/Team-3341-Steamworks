#include <Commands/AutonomousLeft.h>
#include "TurnAndDrive.h"
#include "NavigateCV.h"
#include "../CommandBase.h"
AutonomousLeft::AutonomousLeft(){

	//Requires(drive);
	AddSequential(new TurnAndDrive(39,0));
	AddSequential(new TurnAndDrive(0,0.5));
	//AddSequential(new NavigateCV());
}


