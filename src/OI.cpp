#include <WPILib.h>
#include "Commands/SetDriveReverse.h"
#include "Commands/SetDriveForward.h"
#include "Commands/WinchMove.h"
#include <Commands/WinchPositionControlPID.h>
#include <Commands/SetShooterSpeedPID.h>
#include <Commands/ShooterOff.h>
#include <Commands/CloseGate.h>
#include <Commands/OpenGate.h>
#include "OI.h"
using namespace frc;

OI::OI() :
		driveStickLeft(new Joystick(2)), driveStickRight(new Joystick(1)), operatorStick(
				new Joystick(0)) {
	shooterButtons();
	driveButtons();
	winchButtons();
	// 	: THis doesn't work :'(
	// TODO: FInd good place for these buttons
	//Button* stopWinchPositionPIDButton = new JoystickButton(driveStickRight, 4);
	//shooterButton = new JoystickButton(driveStickRight, 5);
	//shooterButton->WhenPressed(new SetShooterSpeed());
	//new JoystickButton(operatorStick, 1);
	//Button* driveReverse = new JoystickButton(driveStickLeft, 4);
	//driveReverse->WhenPressed(new SetDriveReverse());
	//driveReverse->WhenReleased(new SetDriveForward());

	//Button* togRev = new JoystickButton(driveStickRight, 1);
	//togRev->WhenPressed(new ToggleReverse());

}

void OI::driveButtons() {
	Button* toggleDriveDirection = new JoystickButton(driveStickRight, 3);
	toggleDriveDirection->WhenReleased(new SetDriveReverse());
}
void OI::winchButtons() {
	Button* positionControl = new JoystickButton(operatorStick, 1);
	positionControl->WhenPressed(new PositionControl());
	Button* posCon2 = new JoystickButton(operatorStick, 2);
	posCon2->WhenPressed(new WinchMove);
}

void OI::shooterButtons() {
	Button* shootButt = new JoystickButton(operatorStick, 7); // Shooter On/Off
	shootButt->WhenPressed(new SetShooterSpeed());
	shootButt->WhenReleased(new ShooterOff());

	Button* servoMotor = new JoystickButton(operatorStick, 6); // Open Release Door
	servoMotor->WhenPressed(new OpenGate());
	servoMotor->WhenReleased(new CloseGate());
}

Joystick* OI::getDriveStickLeft() {
	return driveStickLeft;
}

Joystick* OI::getDriveStickRight() {
	return driveStickRight;
}

Joystick* OI::getOperatorStick() {
	return operatorStick;
}

/*Button* OI::getWinchPositionPIDButton()
 {
 return stopWinchPIDButton;
 }*/
/*
 Button* OI::shooterButtonValue()
 {
 return shooterButton;
 }
 */
/*Button* OI::disableShooterButton()
 {
 return disableShooterButton;
 }
 */

/*Button* OI::activatePositionControl()
 {
 return positionControl;
 }*/

OI::~OI() {
	delete driveStickLeft;
	delete driveStickRight;
	delete operatorStick;
	//delete stopWinchPIDButton;
}
