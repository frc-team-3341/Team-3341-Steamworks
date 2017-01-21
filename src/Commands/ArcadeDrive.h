#ifndef ArcadeDrive_H
#define ArcadeDrive_H

#include "CommandBase.h"
#include "../Utilities/WVPIDController.h"
#include "WPILib.h"
//#include ""

class ArcadeDrive: public CommandBase
{
    public:
        ArcadeDrive();
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
