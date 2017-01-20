#ifndef OI_H
#define OI_H

#include "RobotMap.h"
#include "WPILib.h"


class OI
{
    private:
        Joystick* driveStick;
        Joystick* operatorStick;
    public:
        OI();
        ~OI();

        Joystick* getDriveStick();
        Joystick* getOperatorStick();
};

#endif
