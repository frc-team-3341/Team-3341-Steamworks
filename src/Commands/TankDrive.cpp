#include "TankDrive.h"

TankDrive::TankDrive()
    : isReset(true)
{
    Requires(drive);
    anglePid = new WVPIDController(.05, 0, 0, 0, false);
}

void TankDrive::Initialize()
{
    drive->resetGyro();
}

void TankDrive::Execute()
{
    double yLeftRaw = oi->getDriveStickLeft()->GetY();
    double yRightRaw = oi->getDriveStickRight()->GetY();

    double yLeftAdjusted  = mapToCubic(0.3, 0, yLeftRaw);
    double yRightAdjusted = mapToCubic(0.3, 0, yRightRaw);

    drive->tankDrive(-yLeftAdjusted, -yRightAdjusted);
}

// Takes an input signal and maps it to a cubic output (for more precise driving)
double TankDrive::mapToCubic(double a, double b, double signal)
{
    double control;

    if(signal > 0)
        control = b + (1 - b) * ((a * pow(signal, 3) + (1 - a) * signal));
    else
        control = -b + (1 - b) * ((a * pow(signal, 3) + (1 - a) * signal));

    return control;
}

bool TankDrive::IsFinished()
{
    return false;
}

void TankDrive::End()
{
}

void TankDrive::Interrupted()
{
}
