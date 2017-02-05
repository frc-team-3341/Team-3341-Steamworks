#ifndef TankDrive_H
#define TankDrive_H

#include "CommandBase.h"
#include "../Utilities/WVPIDController.h"
#include "WPILib.h"
//#include ""

class TankDrive: public CommandBase
{
    public:
        TankDrive();
        void Initialize();
        void Execute();
        bool IsFinished();
        void End();
        void Interrupted();
    private:
        double mapToCubic(double a, double b, double signal);
        bool isReset;
        WVPIDController* anglePid;
};

#endif
