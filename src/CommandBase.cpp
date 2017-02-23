#include "CommandBase.h"

#include <Commands/Scheduler.h>

#include <Commands/WinchPositionControlPID.h>
#include "Subsystems/Winch.h"
#include "RobotMap.h"
 using namespace frc;

//#include "Subsystems/ExampleSubsystem.h"

// Initialize a single static instance of all of your subsystems. The following
// line should be repeated for each subsystem in the project.
//std::unique_ptr<ExampleSubsystem> CommandBase::exampleSubsystem =
//		std::make_unique<ExampleSubsystem>();
DriveTrain* CommandBase::drive = nullptr;
Shooter* CommandBase::shooter = nullptr;
Winch* CommandBase::winch = nullptr;
std::unique_ptr<OI> CommandBase::oi;

CommandBase::CommandBase(const std::string &name) :
		frc::Command(name) {

}


/* Instantiate static data
 * It is important that subsystems are constructed before OI, which creates commands.
 */
void CommandBase::initialize()
{
	drive = new DriveTrain();
	shooter = new Shooter();
	winch = new Winch(WINCH_PDP_PORT, WINCH_CAN_ID);
	oi = std::make_unique<OI>();
}
