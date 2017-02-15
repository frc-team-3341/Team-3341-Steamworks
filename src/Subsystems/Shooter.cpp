#include <WPILib.h>
#include "../RobotMap.h"
#include "../CommandBase.h"
#include "Commands/SetShooterSpeedPID.h"
#include "Shooter.h"

using namespace frc;

Shooter::Shooter() : Subsystem("Shooter"), shooter(new CANTalon(SHOOTER))
{
	shooter->SetControlMode(CANSpeedController::kPercentVbus);
	shooter->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	shooter->ConfigLimitMode(CANSpeedController::kLimitMode_SrxDisableSwitchInputs);
	shooter->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	shooter->ConfigPeakOutputVoltage(+12.0f, -12.0f); // TODO: figure out through testing
	// encoder = new Encoder(SHOOTERENCODERLEFT); // ENCODER is the pin number for the encoder */
}

void Shooter::setSpeed(double speed)
{
	shooter->Set(speed);

	std::cout << "shooter in class found" << std::endl;
}

void Shooter::setPIDConstants(double F, double P, double I, double D)
{
	shooter->SetF(F);
	shooter->SetP(P); // TODO: Find constants through testing
	shooter->SetI(I);
	shooter->SetD(D);
}

Shooter::~Shooter() //destructor
{
	 delete shooter;
	//delete encoder;
	shooter = NULL;
	// encoder = NULL;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
