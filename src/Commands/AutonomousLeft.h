#ifndef MasterAutonomous_H
#define MasterAutonomous_H

#include <Commands/CommandGroup.h>
#include "../CommandBase.h"

class AutonomousLeft: public CommandGroup {
public:
	AutonomousLeft();
	double* distance;
	double* azimuth;
};

#endif  // MasterAutonomous_H
