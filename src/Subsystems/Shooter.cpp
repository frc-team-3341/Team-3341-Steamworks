#include "Shooter.h"
#include "../RobotMap.h"
using namespace frc;

Shooter::Shooter() : Subsystem("Shooter")
{
	shooter = new CANTalon(LEFTSHOOTER); //SHOOTER is the pin number for the motor
	// encoder = new Encoder(SHOOTERENCODERLEFT); // ENCODER is the pin number for the encoder
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

// TODO: FInd out if this is needed
/* void Shooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
} */

Shooter::~Shooter() //destructor
{
	delete shooter;
	//delete encoder;
	shooter = NULL;
	// encoder = NULL;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
