#include <Commands/AutonomousLeft.h>
#include "TurnAndDrive.h"
#include "NavigateCV.h"
AutonomousLeft::AutonomousLeft(){

	AddSequential(new TurnAndDrive(100,0));
	AddSequential(new TurnAndDrive(0,-90));
	AddSequential(new NavigateCV());
}


