#include "GetCV.h"
#include "Utilities/NetworkTablesInterface.h"

GetCV::GetCV(double* distance, double* azimuth) {
	Requires(drive);
	mDistance = distance;
	mAzimuth = azimuth;
	Initialize();
}

void GetCV::Initialize() {
	finished = false;
}

void GetCV::Execute() {
	if (NetworkTablesInterface::gearFound()) { // Wait Until Gear is Found
		*mDistance = NetworkTablesInterface::getGearDistance();
		*mAzimuth = NetworkTablesInterface::getGearAzimuth();
		finished = true;
	}
}

bool GetCV::IsFinished() {
	return finished;
}

void GetCV::End() {

}

void GetCV::Interrupted() {
	End();
}
