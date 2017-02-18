#include "Commands/SetShooterSpeedPID.h"
#include <WPILib.h>
#include "../RobotMap.h"
#include "../CommandBase.h"
#include "Shooter.h"

using namespace frc;

Shooter::Shooter() : Subsystem("Shooter"), shooter(new CANTalon(SHOOTER))
{
	shooter->SetControlMode(CANSpeedController::kPercentVbus);
	shooter->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	shooter->ConfigLimitMode(CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
	// encoder = new Encoder(SHOOTERENCODERLEFT); // ENCODER is the pin number for the encoder */
}

void Shooter::setSpeed(double speed)
{
	shooter->Set(speed);
	//return shooter->GetSpeed();
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
	shooter->SetF(0);
	shooter->SetP(P); // TODO: Find constants through testing
	shooter->SetI(I);
	shooter->SetD(D);
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
