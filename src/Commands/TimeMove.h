#ifndef TimeMove_H
#define TimeMove_H

#include "CommandBase.h"
#include "WPILib.h"

//#include ""

class TimeMove: public CommandBase
{
public:
	TimeMove(float pspeed, float tspeed, float timeout);
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
private:
	float power, turn, timer;
};

#endif
