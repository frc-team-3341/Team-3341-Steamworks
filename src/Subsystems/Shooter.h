#ifndef Shooter_H
#define Shooter_H
#include <WPILib.h>
#include "Commands/Subsystem.h"
#include "Encoder.h"
#include "CANTalon.h"
using namespace frc;

class Shooter : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
     CANTalon* shooter;
	 double setPoint;
public:
	Shooter();
	~Shooter();
	void setSpeed(double speed);
	void setPID();
	void loadBall();
	void setPIDConstants(double F, double P, double I, double D);

};

#endif  // Shooter_H
