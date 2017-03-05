#include <Commands/AutonomousLeft.h>
#include "Drive.h"
#include "Turn.h"
#include "NavigateCV.h"
#include "TimeMove.h"
#include "GetRobotModelData.h"
#include "../CommandBase.h"

AutonomousLeft::AutonomousLeft() {
	AddSequential(new Drive(128));
	AddSequential(new Turn(60));
	AddSequential(new Drive(35));


	// Move forward while wiggling a bit. Should take 5 seconds
	AddSequential(new TimeMove(-0.1, 0, 0.25)); // Creep forward at the end to ensure peg is in box
	AddSequential(new TimeMove(0.2, 0.2, 1)); // Creep forward at the end to ensure peg is in box
	AddSequential(new TimeMove(0.2, -0.2, 1)); // Creep forward at the end to ensure peg is in box
	AddSequential(new TimeMove(0.2, 0, 1)); // Creep forward at the end to ensure peg is in box
}

