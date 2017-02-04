#include "ShooterAutonomousBlueGroup.h"
#include "../CommandBase.h"

ShooterAutonomousBlueGroup::ShooterAutonomousBlueGroup() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.

	Requires(drive);
	Requires(shooter);
	AddSequential(new TurnAndDrive(distance,45));//drive in an arc to be in front of the target
	AddSequential(new TurnAndDrive(0,90)); //turn to face goal
	AddSequential(new ShooterAutonomous());// need to work on the ShooterAutonomous code
	AddSequential(new TurnAndDrive(0,-135));//turn back
	AddSequential(new TurnAndDrive(100,0));//cross the baseline
}
