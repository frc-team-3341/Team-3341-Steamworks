#ifndef ShooterAutonomous_H
#define ShooterAutonomous_H

#include "../CommandBase.h"
#include "../Utilities/NetworkTablesInterface.h"

class ShooterAutonomous : public CommandBase {
public:
	ShooterAutonomous();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	double findSpeed(double dist);
private:
	double distance;
	double speed;
	double altitude;

};

#endif  // ShooterAutonomous_H
