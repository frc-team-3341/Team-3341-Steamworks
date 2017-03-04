#include <Commands/AutonomousLeft.h>
#include "TurnAndDrive.h"
#include "NavigateCV.h"
#include "TimeMove.h"
#include "GetRobotModelData.h"
#include "../CommandBase.h"

AutonomousLeft::AutonomousLeft()
{
//	AddSequential(new TurnAndDrive(30,0));
//	AddSequential(new TurnAndDrive(0,100));
	AddSequential(new NavigateCV()); // Navigate toward gear using CV
	AddSequential(new TimeMove(0.1, 0, 3)); // Creep forward at the end to ensure peg is in box
}

