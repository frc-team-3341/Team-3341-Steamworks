#ifndef PositionControl_H
#define PositionControl_H
#include <iostream>
#include <memory>
#include <string>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "WPILib.h"
#include "CANTalon.h" /* necessary as of FRC2017, comment out for earler seasons */
#include "../CommandBase.h"
using namespace frc;

class PositionControl : public CommandBase {

private:
	//Joystick * _joy = new Joystick(0);
	std::string _sb;
	int _loops = 0;
	bool _lastButton1 = false;
	/** save the target position to servo to */
	double targetPositionRotations;


public:
	PositionControl();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	void RobotSetClosedPositionLoop(CANTalon* _talon,int movedown);
	void RobotPrintPositionControlLoopStatus(CANTalon* _talon);
	void RobotInit();
	void TeleopPeriodic();

};

#endif  // dummy_H
