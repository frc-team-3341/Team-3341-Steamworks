
#include <memory>

#include "CommandBase.h"
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Utilities/NetworkTablesInterface.h"
#include "Commands/Forward.h"
#include "Subsystems/DriveTrain.h"

class Robot: public frc::IterativeRobot {
public:
	void RobotInit() override {
		CommandBase::initialize();
		//chooser.AddDefault("Default Auto", new ExampleCommand());
		// chooser.AddObject("My Auto", new MyAutoCommand());
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		//foreward = new Forward();
		//left = new Talon(0);
		//right = new Talon(1);
	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() override {

	}

	void DisabledPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to the
	 * chooser code above (like the commented example) or additional comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() override {
		/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
		if (autoSelected == "My Auto") {
			autonomousCommand.reset(new MyAutoCommand());
		}
		else {
			autonomousCommand.reset(new ExampleCommand());
		} */

		autonomousCommand.reset(chooser.GetSelected());

		if (autonomousCommand.get() != nullptr) {
			autonomousCommand->Start();
		}
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand != nullptr) {
			autonomousCommand->Cancel();
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TestInit() override {

		//foreward->Start();
		CommandBase::drive->setSpeedLeft(0.5);
		CommandBase::drive->setSpeedRight(-0.5);
	}

	void TestPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
		frc::SmartDashboard::PutBoolean("CVGearFound", NetworkTablesInterface::gearFound());
		frc::SmartDashboard::PutNumber("CVGearDistance",NetworkTablesInterface::getGearDistance());
		frc::SmartDashboard::PutNumber("CVGearAltitude", NetworkTablesInterface::getGearAltitude());
		frc::SmartDashboard::PutNumber("CVGearAzimuth", NetworkTablesInterface::getGearAzimuth());
	    frc::SmartDashboard::PutBoolean("CVBoilerFound", NetworkTablesInterface::boilerFound());
		frc::SmartDashboard::PutNumber("CVBoilerDistance",NetworkTablesInterface::getBoilerDistance());
		frc::SmartDashboard::PutNumber("CVBoilerAltitude", NetworkTablesInterface::getBoilerAltitude());
		frc::SmartDashboard::PutNumber("CVBoilerAzimuth", NetworkTablesInterface::getBoilerAzimuth());
		frc::LiveWindow::GetInstance()->Run();
	}

private:
	std::unique_ptr<frc::Command> autonomousCommand;
	frc::SendableChooser<frc::Command*> chooser;
	//Command* foreward;
	//Talon* left;
	//Talon* right;
};

START_ROBOT_CLASS(Robot)
