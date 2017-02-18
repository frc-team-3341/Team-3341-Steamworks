#ifndef OI_H
#define OI_H

#include "RobotMap.h"
#include <WPILib.h>

using namespace frc;

class OI
{
    private:
        Joystick* driveStickLeft;
        Joystick* driveStickRight;
        Joystick* operatorStick;
        Button* stopWinchPIDButton;
        Button* shooterButton;
    public:
        OI();
        ~OI();

        Joystick* getDriveStickLeft();
        Joystick* getDriveStickRight();
        Joystick* getOperatorStick();
        Button* getWinchPositionPIDButton();
        Button* shooterButtonValue();
};

#endif
