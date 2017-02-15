#ifndef WinchPositionPID_H
#define WinchPositionPID_H

#include "../CommandBase.h"
#include "CANTalon.h"

class WinchPositionPID : public CommandBase {

private:
	CANTalon* _talon;
	std::string _sb;
	int _loops;
	bool _lastButton1;
	/** save the target position to servo to */
	double targetPositionRotations;
	double currentPoint;
	double setPoint;
	double correctionValue;
	double moveValue;
	double distFromSetPoint;


public:
	WinchPositionPID();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // WinchClimbPID_H
