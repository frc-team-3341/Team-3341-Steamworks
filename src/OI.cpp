#include <Commands/SetShooterSpeedPID.h>
#include "OI.h"
#include <WPILib.h>
#include "Commands/SetDriveReverse.h"
#include "Commands/SetDriveForward.h"

OI::OI():
	driveStickLeft(new Joystick(0)), driveStickRight(new Joystick(1)), operatorStick(new Joystick(2))
{
	// TODO: THis doesn't work :'(
	// TODO: FInd good place for these buttons
	Button* stopWinchPositionPIDButton = new JoystickButton(driveStickRight, 4);
	Button* shooterButton = new JoystickButton(driveStickRight, 5);
	shooterButton->WhenPressed(new SetShooterSpeed());
 	//Button* driveReverse = new JoystickButton(driveStickLeft, 4);
	//driveReverse->WhenPressed(new SetDriveReverse());
	//driveReverse->WhenReleased(new SetDriveForward());
}

Joystick* OI::getDriveStickLeft()
{
    return driveStickLeft;
}

Joystick* OI::getDriveStickRight()
{
    return driveStickRight;
}

Joystick* OI::getOperatorStick()
{
    return operatorStick;
}

Button* OI::getWinchPositionPIDButton()
{
	return stopWinchPIDButton;
}

Button* OI::shooterButtonValue()
{
	return shooterButton;
}

/*Button* OI::disableShooterButton()
{
	return disableShooterButton;
}
*/

OI::~OI()
{
    delete driveStickLeft;
    delete driveStickRight;
    delete operatorStick;
    delete stopWinchPIDButton;
}
