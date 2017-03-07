#ifndef OI_H
#define OI_H

#include "RobotMap.h"
#include "WPILib.h"

class OI {
private:
	Joystick* driveStickLeft;
	Joystick* driveStickRight;
	Joystick* operatorStick;
	//Button* stopWinchPIDButton;
	//Button* positionControl;
	//Button* shooterButton;

	void driveButtons();
	void winchButtons();
	void shooterButtons();

public:
	OI();
	~OI();

	Joystick* getDriveStickLeft();
	Joystick* getDriveStickRight();
	Joystick* getOperatorStick();
};

#endif
