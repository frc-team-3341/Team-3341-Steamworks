#ifndef MasterAutonomous_H
#define MasterAutonomous_H

#include <Commands/CommandGroup.h>
#include "../CommandBase.h"

class AutonomousSide: public CommandGroup {
public:
	AutonomousSide(bool left);
	double distance;
	double azimuth;
};

#endif  // MasterAutonomous_H
