#include <Commands/WinchPositionPID.h>

WinchPositionPID::WinchPositionPID()
{
	 //_loops = 0;
	 _lastButton1 = false;
	 _talon->SetControlMode(CANSpeedController::kPercentVbus);
	 _talon->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	 _talon->ConfigLimitMode(CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
	 // Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());

}

// Called just before this Command runs the first time
void WinchPositionPID::Initialize()
{
	/* lets grab the 360 degree position of the MagEncoder's absolute position */
			// int absolutePosition = _talon->GetPulseWidthPosition() & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
			/* use the low level API to set the quad encoder signal */

			/* set the peak and nominal outputs, 12V means full */
			//_talon->ConfigNominalOutputVoltage(+0., -0.); //TODO: See if needed
			//_talon->ConfigPeakOutputVoltage(+12., -12.); //TODO: See if needed
			/* set the allowable closed-loop error,
			 * Closed-Loop output will be neutral within this range.
			 * See Table in Section 17.2.1 for native units per rotation.
			 */
			//_talon->SetAllowableClosedLoopErr(0); /* always servo */
			/* set closed loop gains in slot0 */
			//_talon->SelectProfileSlot(0);
			_talon->SetF(1); // TODO: Set F constant through testing
			_talon->SetP(1); // TODO: Set P constant through testing
			_talon->SetI(0.0); // TODO: Set I constant through testing
			_talon->SetD(0.0); // TODO: Set D constant through testing
			 // TODO: set correctionValue through testing
			setPoint = (_talon->GetPosition() - correctionValue);
}

// Called repeatedly when this Command is scheduled to run
void WinchPositionPID::Execute()
{
	currentPoint = _talon->GetPosition();
	distFromSetPoint = (setPoint - currentPoint);
	// 5.655 is the circumference of winch with rope
	targetPositionRotations = (distFromSetPoint / 19.792);
	_talon->Set(targetPositionRotations);

}

// Make this return true when this Command no longer needs to run execute()
bool WinchPositionPID::IsFinished()
{
	if(_lastButton1 == true)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void WinchPositionPID::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WinchPositionPID::Interrupted()
{

}
