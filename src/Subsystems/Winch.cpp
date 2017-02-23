#include "Winch.h"
#include "../RobotMap.h"
#include "WPILib.h"
#include "../Commands/WinchMove.h"


Winch::Winch(int portNumber, uint32_t canID):
	Subsystem("Winch"),talonMotor(new CANTalon(canID)),
//distEncoder(new Encoder(WINCH_ENCODER1 ,WINCH_ENCODER2)),
	winchPortNumber(portNumber),
	canBUSID(canID)
{
	//distEncoder->SetDistancePerPulse(1.0);
}

void Winch::InitDefaultCommand()
{
	SetDefaultCommand(new WinchMove());
}

Winch::~Winch()
{
   //delete distEncoder;
   delete talonMotor;

}

void Winch::resetEncoder()
{
    //distEncoder->Reset();
}

double Winch::getCurrent()
{
	double current = pdp.GetCurrent(winchPortNumber);
	return current;

}

double Winch::getDistance()
{
    // Average of both encoders (must negate to get proper direction)
	return 0;
    //return distEncoder->GetDistance();

}

CANTalon *Winch::getTalon()
{
	return talonMotor;
}

double Winch::getRate()
{

    return 0;//distEncoder->GetRate();

}

void Winch::setSpeed(double s)
{
    talonMotor->Set(s);

}

void Winch::stopMotor()
{
	talonMotor->Set(0);

}

// Put methods for controlling this subsystem
// here. Call these from Commands.
