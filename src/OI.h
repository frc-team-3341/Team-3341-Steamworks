#ifndef OI_H
#define OI_H

#include "RobotMap.h"
#include "WPILib.h"


class OI
{
    private:
        Joystick* driveStickLeft;
        Joystick* driveStickRight;
        Joystick* operatorStick;
    public:
        OI();
        ~OI();

        Joystick* getDriveStickLeft();
        Joystick* getDriveStickRight();
        Joystick* getOperatorStick();
};

#endif
