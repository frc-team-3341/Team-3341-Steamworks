#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter")
{
	shooter = new TalonSRX(SHOOTER); //SHOOTER is the pin number for the motor
	encoder = new Encoder(ENCODER); // ENCODER is the pin number for the encoder
}

void Shooter::setSpeed(double speed)
{
	shooter->SetSpeed(speed);
}

double Shooter::getRate()
{
	return encoder->GetRate();
}

void Shooter::resetEncoder()
{
	encoder->Reset();
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
	delete encoder;
	shooter = NULL;
	encoder = NULL;
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
