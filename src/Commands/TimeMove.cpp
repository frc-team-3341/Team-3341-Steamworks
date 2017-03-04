#include "TimeMove.h"

TimeMove::TimeMove(float pspeed, float tspeed, float timeout)
{
	Requires(drive);
	power = pspeed;
	turn = tspeed;
	timer = timeout;
	Initialize();
}

void TimeMove::Initialize()
{
	SetTimeout(timer);
}

void TimeMove::Execute()
{
	drive->arcadeDrive(power, turn);
}

bool TimeMove::IsFinished()
{
	return IsTimedOut();
}

void TimeMove::End()
{
	drive->arcadeDrive(0, 0);
}

void TimeMove::Interrupted()
{
	End();
}
