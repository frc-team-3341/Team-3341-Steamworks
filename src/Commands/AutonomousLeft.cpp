#include <Commands/AutonomousLeft.h>
#include "Drive.h"
#include "Turn.h"
#include "NavigateCV.h"
#include "TimeMove.h"
#include "GetRobotModelData.h"
#include "../CommandBase.h"

AutonomousLeft::AutonomousLeft() {
	AddSequential(new Drive(20));
	AddSequential(new Turn(90));
//	AddSequential(new TurnAndDrive(0,100));
//  AddSequential(new NavigateCV()); // Navigate toward gear using CV
//	AddSequential(new TimeMove(0.1, 0, 3)); // Creep forward at the end to ensure peg is in box
}

