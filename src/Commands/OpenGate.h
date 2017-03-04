#ifndef OpenGate_H
#define OpenGate_H

#include "../CommandBase.h"

class OpenGate: public CommandBase
{
public:
	OpenGate();
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // OpenGate_H
