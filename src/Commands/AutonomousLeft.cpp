#include <Commands/AutonomousLeft.h>
#include "Drive.h"
#include "Turn.h"
#include "Delay.h"
#include "GetCV.h"
#include "TimeMove.h"
#include "GetRobotModelData.h"
#include "../CommandBase.h"

AutonomousLeft::AutonomousLeft() {
	AddSequential(new Drive(128,1));
	AddSequential(new Turn(60));
	AddSequential(new Drive(10, 1)); // Move forward a short distance
	AddSequential(new Delay(2)); // Delay for 2 seconds
	AddSequential(new GetCV(distance, azimuth)); // Get CV Values
	AddSequential(new Turn(*azimuth));
	AddSequential(new Drive(*distance * 39.3701, 0.3)); // Drive the rest of the distance to the target, and convert CV meters to inches
}

