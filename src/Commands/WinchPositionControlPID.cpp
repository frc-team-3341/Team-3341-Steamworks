#include <Commands/WinchPositionControlPID.h>
#include <iostream>
#include "CANTalon.h"

PositionControl::PositionControl() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(winch);

}

// Called just before this Command runs the first time
void PositionControl::Initialize() {
	//winch->getTalon()->Set(0.5);
	RobotSetClosedPositionLoop(winch->getTalon(), 0);
}

// Called repeatedly when this Command is scheduled to run
void PositionControl::Execute() {
	RobotPrintPositionControlLoopStatus(winch->getTalon());
}

// Make this return true when this Command no longer needs to run execute()
bool PositionControl::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void PositionControl::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionControl::Interrupted() {
}

void PositionControl::RobotInit() {

}

void PositionControl::RobotPrintPositionControlLoopStatus(CANTalon* _talon) {
	/* if Talon is in position closed-loop, print some more info */
	//int absolutePosition = _talon->GetPulseWidthPosition() & 0xFFF;
	//if (_talon->GetClosedLoopError() == absolutePosition)
	if (_talon->GetControlMode() == CANSpeedController::kPosition) {
		/* append more signals to print when in speed mode. */
		_sb.append("\terrNative:");
		_sb.append(std::to_string(_talon->GetClosedLoopError()));
		_sb.append("\ttrg:");
		_sb.append(std::to_string(targetPositionRotations));
		_sb.append("\tCurrentPosition:");
		int absolutePosition = _talon->GetPulseWidthPosition() & 0xFFF;
		_sb.append(std::to_string(absolutePosition));
	}
	/* print every ten loops, printing too much too fast is generally bad for performance */
	if (++_loops >= 10) {
		_loops = 0;
		printf("%s\n", _sb.c_str());
	}
	_sb.clear();
}

void PositionControl::RobotSetClosedPositionLoop(CANTalon* _talon,
		int movedown) {
	/* lets grab the 360 degree position of the MagEncoder's absolute position */
	int absolutePosition = _talon->GetPulseWidthPosition() & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	/* use the low level API to set the quad encoder signal */
	//_talon->SetEncPosition(absolutePosition);

	/* choose the sensor and sensor direction */
	//_talon->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	_talon->SetFeedbackDevice(CANTalon::QuadEncoder);
	_talon->SetSensorDirection(true);
	//_talon->ConfigEncoderCodesPerRev(360); // if using FeedbackDevice.QuadEncoder
	//_talon->ConfigPotentiometerTurns(XXX), // if using FeedbackDevice.AnalogEncoder or AnalogPot

	/* set the peak and nominal outputs, 12V means full */
	_talon->ConfigNominalOutputVoltage(+0., -0.);
	_talon->ConfigPeakOutputVoltage(+12., -12.);
	/* set the allowable closed-loop error,
	 * Closed-Loop output will be neutral within this range.
	 * See Table in Section 17.2.1 for native units per rotation.
	 */
	_talon->SetAllowableClosedLoopErr(0); /* always servo */
	/* set closed loop gains in slot0 */
	_talon->SelectProfileSlot(0);
	_talon->SetF(0.0);
	_talon->SetP(0.5);
	_talon->SetI(0.0);
	_talon->SetD(0.0);

	targetPositionRotations = absolutePosition;
	_talon->SetPosition(0.0);
	_talon->SetControlMode(CANSpeedController::kPosition);
	_talon->Set(0.0); /* 50 rotations in either direction */
}

void PositionControl::TeleopPeriodic() {
	/* get gamepad axis */
#if 0
	double leftYstick = _joy->GetAxis(Joystick::kYAxis);
	double motorOutput = _talon->GetOutputVoltage() / _talon->GetBusVoltage();
	bool button1 = _joy->GetRawButton(1);
	bool button2 = _joy->GetRawButton(2);
	/* prepare line to print */
	_sb.append("\tout:");
	_sb.append(std::to_string(motorOutput));
	_sb.append("\tpos:");
	_sb.append(std::to_string(_talon->GetPosition()));
	/* on button1 press enter closed-loop mode on target position */
	if (!_lastButton1 && button1)
	{
		/* Position mode - button just pressed */

		targetPositionRotations = leftYstick * 50.0; /* 50 Rotations in either direction */
#endif
#if 0
	targetPositionRotations = 2 * 50.0;
	_talon->SetControlMode(CANSpeedController::kPosition);
	_talon->Set(targetPositionRotations); /* 50 rotations in either direction */
#endif
#if 0
}
/* on button2 just straight drive */
if (button2)
{
	/* Percent voltage mode */
	_talon->SetControlMode(CANSpeedController::kPercentVbus);
	_talon->Set(leftYstick);
}
#endif
	RobotPrintPositionControlLoopStatus(winch->getTalon());
#if 0
	/* save button state for on press detect */
	_lastButton1 = button1;
#endif

}

