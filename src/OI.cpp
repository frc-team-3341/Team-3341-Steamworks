#include "OI.h"

using namespace frc;

OI::OI():
	driveStick(new Joystick(0)), operatorStick(new Joystick(1))
{

}

Joystick* OI::getDriveStick()
{
    return driveStick;
}

Joystick* OI::getOperatorStick()
{
    return operatorStick;
}

OI::~OI()
{
    delete driveStick;
    delete operatorStick;
}
