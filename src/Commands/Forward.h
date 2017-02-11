#ifndef Forward_H
#define Forward_H

#include "../CommandBase.h"

class Forward : public CommandBase {
public:
	Forward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Forward_H
