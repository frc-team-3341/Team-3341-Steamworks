#ifndef SetDriveForward_H
#define SetDriveForward_H

#include "../CommandBase.h"

class SetDriveForward : public CommandBase {
public:
	SetDriveForward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SetDriveForward_H
