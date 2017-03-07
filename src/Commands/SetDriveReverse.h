#ifndef SetDriveReverse_H
#define SetDriveReverse_H

#include "../CommandBase.h"

class SetDriveReverse: public CommandBase {
public:
	SetDriveReverse();
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
	bool done;
};

#endif  // SetDriveReverse_H
