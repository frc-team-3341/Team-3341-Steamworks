#include <WPILib.h>
#include "../RobotMap.h"
#include "../CommandBase.h"
#include "Shooter.h"

using namespace frc;

Shooter::Shooter() : Subsystem("Shooter")
{
	shooter = new CANTalon(LEFTSHOOTER); //SHOOTER is the pin number for the motor
	shooter->SetTalonControlMode(CANTalon::kSpeedMode);
	shooter->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);
	shooter->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	shooter->ConfigPeakOutputVoltage(+12.0f, -12.0f); // TODO: figure out through testing
	// encoder = new Encoder(SHOOTERENCODERLEFT); // ENCODER is the pin number for the encoder */
}

void Shooter::setSpeed(double speed)
{
	shooter->Set(speed);
}

void Shooter::setPIDConstants()
{
	shooter->SetP(0.5); // TODO: Find constants through testing
	shooter->SetI(0);
	shooter->SetD(0);
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
