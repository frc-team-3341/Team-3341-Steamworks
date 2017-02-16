#include "Commands/TurnAndDrive.h"

TurnAndDrive::TurnAndDrive(double inDistance, double inAngle)
    : distance(inDistance * PIDCON_INCHES * 1.185), angle(inAngle)
{
    Requires(drive);
    distancePid = NULL;
    anglePid = NULL;
    forceFinish = false;
}

void TurnAndDrive::Initialize()
{
    SetTimeout(2.2);
    drive->resetEncoders();
    drive->resetGyro();
    distancePid = new WVPIDController(0.15, 0.0, 0.0, distance, false);
    anglePid = new WVPIDController(0.05, 1e-2, 0, angle, false); // kp was 0.1 before,works for low bar
}

void TurnAndDrive::Execute()
{
    double current_distance = drive->getDistance();
    double pwm_val = distancePid->Tick(current_distance);
    double current_angle = drive->getGyroAngle();
    double rotateVal = anglePid->Tick(current_angle);

    std::cout << "ERROR!!!!: " << distancePid->GetError() << std::endl;
    std::cout << "curr_dist: " << drive->getDistance() << std::endl;
    std::cout << "pwm: " << pwm_val << std::endl;


    //std::cout << "Gyro PV: " << current_angle << std::endl;
   // std::cout << "Gyro error: " << anglePid->GetError() << std::endl;

    drive->arcadeDrive(DriveTrain::Limit(pwm_val, 0.3), -DriveTrain::Limit(rotateVal, 0.5));
}

bool TurnAndDrive::IsFinished()
{
    bool finished =
    (
        (
            (fabs(distancePid->GetError()) < 0.005)
            && (fabs(anglePid->GetError()) < 0.01)
            //&& (fabs(drive->GetRate()) < 1e-3)
        )
    );
    if(finished) std::cout << "Autonomous finished" << std::endl;
    return finished || forceFinish;
}

void TurnAndDrive::ForceFinish()
{
    forceFinish = true;
}

void TurnAndDrive::End()
{
    drive->arcadeDrive(0, 0);
}

void TurnAndDrive::Interrupted()
{
}
