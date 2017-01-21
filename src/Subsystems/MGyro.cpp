#include "MGyro.h"
#include "../RobotMap.h"

MGyro::MGyro() :
		Subsystem("MGyro")
{
		gyro = new AnalogGyro(0);
	    gyro->Calibrate();
	    gyro->Reset();
}

void MGyro::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

double MGyro::GetAngle()
{
    return -gyro->GetAngle();
}

void MGyro::ResetGyro()
{
    gyro->Reset();
}
