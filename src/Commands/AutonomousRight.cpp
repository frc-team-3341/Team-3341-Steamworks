#include "AutonomousRight.h"
#include "TurnAndDrive.h"
#include "NavigateCV.h"
AutonomousRight::AutonomousRight() {


	//Requires(drive);
	    AddSequential(new TurnAndDrive(100,0));
		AddSequential(new TurnAndDrive(0,90));
		//AddSequential(new NavigateCV());
}

