#ifndef Shooter_H
#define Shooter_H

#include <Commands/Subsystem.h>
using namespace frc;

class Shooter : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	 TalonSRX* shooter;
	 Encoder* encoder;

public:

	Shooter();
	void InitDefaultCommand();
	~Shooter();
	//void InitDefaultCommand(); // TODO: FInd out if this is needed
	void setSpeed(double speed);
	double getRate();
	void loadBall();
	void resetEncoder();

};

#endif  // Shooter_H
