#include "Shooter.h"
#include "../RobotMap.h"
using namespace frc;

Shooter::Shooter() :
		Subsystem("Shooter"), shooter(new CANTalon(SHOOTER)), servo(
				new Servo(2))
{
	shooter->SetControlMode(CANSpeedController::kPercentVbus);
	shooter->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	//shooter->ConfigLimitMode(CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
	// encoder = new Encoder(SHOOTERENCODERLEFT); // ENCODER is the pin number for the encoder
}

void Shooter::setSpeed(double speed)
{
	shooter->Set(speed);
}

double Shooter::getSpeed()
{
	return shooter->GetSpeed();
}

double Shooter::getEncoderVel()
{
	return shooter->GetEncVel();
}

bool Shooter::disable(bool button)
{
	return button;
}

void Shooter::setPIDConstants(double F, double P, double I, double D)
{
	shooter->SetF(F);
	shooter->SetP(P); // TODO: Find constants through testing
	shooter->SetI(I);
	shooter->SetD(D);
}

void Shooter::setServo(int angle)
{
	servo->SetAngle(angle);
}

/*Shooter::~Shooter() //destructor
 {
 delete shooter;
 //delete encoder;
 shooter = NULL;
 // encoder = NULL;
 } */

// Put methods for controlling this subsystem
// here. Call these from Commands.
