#include "OI.h"
#include "Commands/SetDriveReverse.h"
#include "Commands/SetDriveForward.h"

using namespace frc;

OI::OI():
	driveStickLeft(new Joystick(0)), driveStickRight(new Joystick(1)), operatorStick(new Joystick(2))
{
	// TODO: THis doesn't work :'(
	Button* driveReverse = new JoystickButton(driveStickLeft, 4);
	driveReverse->WhenPressed(new SetDriveReverse());
	driveReverse->WhenReleased(new SetDriveForward());
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

OI::~OI()
{
    delete driveStickLeft;
    delete driveStickRight;
    delete operatorStick;
}
