#ifndef WinchMove_H
#define WinchMove_H

#include "../CommandBase.h"
#include "../Subsystems/Winch.h"
#include "OI.h"
using namespace frc;

class WinchMove : public CommandBase {

private:
	Joystick* winchMove;
	CANTalon* _talon;
	bool _lastButton1;
	double setPoint;


public:
	WinchMove();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // WinchSpeedPID_H
