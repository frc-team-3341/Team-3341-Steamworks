#ifndef Autonomous_Center_H
#define Autonomous_Center_H

#include <Commands/CommandGroup.h>
#include "../CommandBase.h"

class AutonomousCenter: public CommandGroup {
public:
	AutonomousCenter();
	double distance;
	double azimuth;
};

#endif  // MasterAutonomous_H
