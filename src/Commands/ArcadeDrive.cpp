#include "ArcadeDrive.h"

ArcadeDrive::ArcadeDrive()
    : isReset(true)
{
    Requires(drive);
    anglePid = new WVPIDController(.05, 0, 0, 0, false);
}

void ArcadeDrive::Initialize()
{
    drive->resetGyro();
}

void ArcadeDrive::Execute()
{
    double rotRaw = oi->getDriveStickLeft()->GetZ();
    double yRaw = oi->getDriveStickLeft()->GetY();
    double yAdjusted = mapToCubic(0.4, 0, yRaw);

    // Joystick is turning, turn normally
    if(fabs(rotRaw) >= 0.05)
    {
    	// Flag the gyro for reseting next time we try to drive straight
        isReset = false;

		double rotAdjusted = mapToCubic(0.3, 0, rotRaw);
        drive->arcadeDrive(-yAdjusted, -rotAdjusted);
    }
    else // Joystick is straight, use Gyro to drive straight
    {
        // Reset the Gyro sensor once only
        if(!isReset)
        {
            drive->arcadeDrive(0, 0);
           // Wait(.05);
            isReset = true;
            drive->resetGyro();
        }

    	double angle = drive->getGyroAngle();
    	double correctedAngleSignal = anglePid->Tick(angle);

        // Feed the angle from the Gyro into the PID loop; use returned value from PID loop to drive straight
        if(fabs(yRaw) >= .05)
        {
            drive->arcadeDrive(-yAdjusted, correctedAngleSignal);
        }
        else
        {
            // Brake the drive wheels
            drive->arcadeDrive(0, 0);
        }
    }
}

// Takes an input signal and maps it to a cubic output (for more precise driving)
double ArcadeDrive::mapToCubic(double a, double b, double signal)
{
    double control;

    if(signal > 0)
        control = b + (1 - b) * ((a * pow(signal, 3) + (1 - a) * signal));
    else
        control = -b + (1 - b) * ((a * pow(signal, 3) + (1 - a) * signal));

    return control;
}

bool ArcadeDrive::IsFinished()
{
    return false;
}

void ArcadeDrive::End()
{
}

void ArcadeDrive::Interrupted()
{
}
