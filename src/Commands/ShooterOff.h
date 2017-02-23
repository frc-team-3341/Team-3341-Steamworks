#ifndef ShooterOff_H
#define ShooterOff_H

#include "../CommandBase.h"

class ShooterOff : public CommandBase {
public:
	ShooterOff();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ShooterOff_H
