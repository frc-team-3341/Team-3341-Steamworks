#ifndef DriveXFeet_H
#define DriveXFeet_H

#include "../../CommandBase.h"
#include "../../Utilities/WVPIDController.h"
#include "WPILib.h"

class TurnAndDrive: public CommandBase
{
    public:
        TurnAndDrive(double distance, double angle);
        void Initialize();
        void Execute();
        bool IsFinished();
        void End();
        void Interrupted();
        void ForceFinish();

    private:
        double distance;
        double angle;
        bool forceFinish;
        WVPIDController* distancePid;
        WVPIDController* anglePid;
};

#endif
