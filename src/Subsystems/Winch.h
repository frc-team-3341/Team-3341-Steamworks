#ifndef Winch_H
#define Winch_H
#include "CANTalon.h"

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Winch: public Subsystem
{
private:
	CANTalon* talonMotor;
	//Encoder* distEncoder;
	PowerDistributionPanel pdp;
	int winchPortNumber = 0;
	uint32_t canBUSID;

public:
	Winch(int portNumber, uint32_t canID);
	~Winch();
	CANTalon * getTalon();
	double getDistance();
	double getRate();
	double getCurrent();
	void resetEncoder();
	void setSpeed(double s);
	void stopMotor();
	void InitDefaultCommand();

};

#endif
