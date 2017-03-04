// eg. Requires(Robot::chassis.get());
#include <Commands/WinchMove.h>
#include <RobotMap.h>

WinchMove::WinchMove()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(winch);
	// TODO:: Find joystick port
	// winchMove = oi->getOperatorStick();
	_talon = new CANTalon(WINCH_CAN_ID);
	_lastButton1 = false;
	setPoint = 0;
	//_talon->SetControlMode(CANSpeedController::kPercentVbus);
	//_talon->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	// _talon->ConfigLimitMode(CANSpeedController::kLimitMode_SrxDisableSwitchInputs);

}

// Called just before this Command runs the first time
void WinchMove::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void WinchMove::Execute()
{
	setPoint = -oi->getOperatorStick()->GetY();
	_talon->Set(setPoint);
}

// Make this return true when this Command no longer needs to run execute()
bool WinchMove::IsFinished()
{
	if (_lastButton1 == true)
	{
		return true;
	}
	return false;
}

void WinchMove::End()
{

}

void WinchMove::Interrupted()
{

}
