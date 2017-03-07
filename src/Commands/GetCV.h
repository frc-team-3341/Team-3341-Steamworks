#ifndef GetCV_H
#define GetCV_H

#include "CommandBase.h"
#include "Utilities/NetworkTablesInterface.h"
#include "WPILib.h"

//#include ""

class GetCV: public CommandBase {
public:
	GetCV(double* distance, double* azimuth);
	void Initialize();
	void Execute();bool IsFinished();
	void End();
	void Interrupted();
private:
	double* mAzimuth;
	double* mDistance;
	bool finished;
};

#endif
