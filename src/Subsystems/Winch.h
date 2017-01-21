#ifndef Winch_H
#define Winch_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Winch: public Subsystem
{
private:
	TalonSRX* talonMotor;
	Encoder* distEncoder;
public:
	Winch();
	~Winch();
	double getDistance();
	double getRate();
	void resetEncoder();
	void setSpeed(double s);
	void stopMotor ();
	void InitDefaultCommand();

};

#endif
