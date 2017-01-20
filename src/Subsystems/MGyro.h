#ifndef MGyro_H
#define MGyro_H

#include "Commands/Subsystem.h"
#include "WPILib.h"


class MGyro: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	AnalogGyro* gyro;
public:
	MGyro();
	void InitDefaultCommand();
	double GetAngle();
	void ResetGyro();
};

#endif
