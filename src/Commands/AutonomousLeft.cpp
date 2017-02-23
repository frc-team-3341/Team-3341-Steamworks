#include <Commands/AutonomousLeft.h>
#include "TurnAndDrive.h"
#include "NavigateCV.h"
#include "../CommandBase.h"
AutonomousLeft::AutonomousLeft(){

	//Requires(drive);
	//AddSequential(new CVDrive());
	//AddSequential(new TurnAndDrive(30,0));
	//AddSequential(new TurnAndDrive(0,100));
	AddSequential(new NavigateCV());
}


