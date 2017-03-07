#include <Commands/AutonomousCenter.h>
#include "Drive.h"
#include "Turn.h"
#include "Delay.h"
#include "GetCV.h"
#include "TimeMove.h"
#include "GetRobotModelData.h"
#include "../CommandBase.h"

AutonomousCenter::AutonomousCenter(bool left) {
	AddSequential(new Drive(90,0.5));
	AddSequential(new Delay(2)); // Delay for 2 seconds
	AddSequential(new GetCV(&distance, &azimuth)); // Get CV Values
	AddSequential(new Turn(&azimuth));
	AddSequential(new Drive(distance - 7, 0.2)); // Drive the rest of the distance to the target, and convert CV meters to inches
}

