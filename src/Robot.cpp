#include <Commands/AutonomousSide.h>
#include <Commands/AutonomousCenter.h>
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
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <Commands/WinchPositionControlPID.h>
#include "Subsystems/Winch.h"

using namespace frc;

class Robot: public frc::IterativeRobot {

private:
	//wvrobotics::NewGyro* gyro;
	//wvrobotics::GyroAxis axis;

	std::unique_ptr<frc::Command> autoCommand;
	int flag = 0;
	int startupTime = 5;
	//std::unique_ptr<Command> autonomousCommand;
	//Shooter* shooter;
public:

	static void VisionThread3() {

		// Get the USB camera from CameraServer
		cs::UsbCamera camera =
				CameraServer::GetInstance()->StartAutomaticCapture(
						"USB Camera 0", 0);
		// Set the resolution
		camera.SetResolution(640, 480);

		// Get a CvSink. This will capture Mats from the Camera
		cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
		// Setup a CvSource. This will send images back to the Dashboard
		cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo(
				"USB Camera 0", 640, 480);

		// Mats are very memory expensive. Lets reuse this Mat.
		cv::Mat mat;

		while (true) {
			// Tell the CvSink to grab a frame from the camera and put it
			// in the source mat.  If there is an error notify the output.
			if (cvSink.GrabFrame(mat) == 0) {
				// Send the output the error.
				outputStream.NotifyError(cvSink.GetError());
				// skip the rest of the current iteration
				continue;
			}
			// Put a rectangle on the image
			rectangle(mat, cv::Point(100, 100), cv::Point(400, 400),
					cv::Scalar(255, 255, 255), 5);
			// Give the output stream a new image to display
			outputStream.PutFrame(mat);
		}
	}
	static void VisionThread4() {

		// Get the USB camera from CameraServer
		cs::UsbCamera camera1 =
				CameraServer::GetInstance()->StartAutomaticCapture(
						"USB Camera 1", 1);

		// Set the resolution
		camera1.SetResolution(640, 480);

		// Get a CvSink. This will capture Mats from the Camera
		cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
		// Setup a CvSource. This will send images back to the Dashboard
		cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo(
				"USB Camera 1", 640, 480);

		// Mats are very memory expensive. Lets reuse this Mat.
		cv::Mat mat;

		while (true) {
			// Tell the CvSink to grab a frame from the camera and put it
			// in the source mat.  If there is an error notify the output.
			if (cvSink.GrabFrame(mat) == 0) {
				// Send the output the error.
				outputStream.NotifyError(cvSink.GetError());
				// skip the rest of the current iteration
				continue;
			}
			// Put a rectangle on the image
			rectangle(mat, cv::Point(100, 100), cv::Point(400, 400),
					cv::Scalar(255, 255, 255), 5);
			// Give the output stream a new image to display
			outputStream.PutFrame(mat);
		}
	}
	void RobotInit() override
	{

		CommandBase::initialize();

		chooser.AddDefault("Autonomous Left", new AutonomousSide(true));
		chooser.AddObject("Autonomous Right", new AutonomousSide(false));
		chooser.AddObject("Autonomous Center", new AutonomousCenter());

		frc::SmartDashboard::PutData("Auto Modes", &chooser);

		//shooter = new Shooter();
		//drivingCommand = new AutonomousRight();
		//gyro = new wvrobotics::NewGyro(I2C::kOnboard, 0x6b); //50 is the calibration sample size; can change it as desired
		std::thread visionThread3(VisionThread3);
		visionThread3.detach();
		std::chrono::milliseconds timespan(5000); // 5000 milliseconds can be changed to a certain time
		std::this_thread::sleep_for(timespan);
		std::thread visionThread4(VisionThread4);
		visionThread4.detach();

		//foreward = new Forward();
		//left = new Talon(0);
		//right = new Talon(1);
	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() override
	{
		CommandBase::drive->gyro->periodicProcessing(startupTime);
	}

	void DisabledPeriodic() override
	{
		CommandBase::drive->gyro->periodicProcessing(startupTime);
		frc::Scheduler::GetInstance()->Run();

		frc::SmartDashboard::PutNumber("Gyro",
				CommandBase::drive->getGyroAngle());
		frc::SmartDashboard::PutNumber("EncoderTest",
				CommandBase::drive->getLeftEncoderDistance());
		frc::SmartDashboard::PutNumber("EncoderRight",
				CommandBase::drive->getRightEncoderDistance());
		frc::SmartDashboard::PutBoolean("CVGearFound",
				NetworkTablesInterface::gearFound());
		frc::SmartDashboard::PutNumber("CVGearDistance",
				NetworkTablesInterface::getGearDistance());
		frc::SmartDashboard::PutNumber("CVGearAltitude",
				NetworkTablesInterface::getGearAltitude());
		frc::SmartDashboard::PutNumber("CVGearAzimuth",
				NetworkTablesInterface::getGearAzimuth());

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
	void AutonomousInit() override
	{
		CommandBase::drive->gyro->periodicProcessing(startupTime);
		// std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
		//int mode = (int) chooser.GetSelected();
		/*if (autoSelected == "Driving") {
		 autonomousCommand.reset(drivingCommand);
		 }*/

		//else {
		//autonomousCommand.reset(new ExampleCommand());
		//}
		//autonomousCommand.reset(chooser.GetSelected());
		/*if(autoSelected == "Driving"){
		 drivingCommand->Start();
		 }
		 else {
		 turningCommand->Start();
		 }*/

		autoCommand.reset(chooser.GetSelected());
		if (autoCommand.get() != nullptr) {
			autoCommand->Start();
		}
	}

	void AutonomousPeriodic() override
	{
		CommandBase::drive->gyro->periodicProcessing(startupTime);
		frc::Scheduler::GetInstance()->Run();

	}

	void TeleopInit() override
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		/*std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
		 if(autoSelected == "Driving"){
		 drivingCommand->Cancel();
		 }
		 else {
		 turningCommand->Cancel();
		 }*/

		if (autoCommand.get() != nullptr) {
			autoCommand->Cancel();
		}
	}

	void TeleopPeriodic() override
	{
		CommandBase::drive->gyro->periodicProcessing(startupTime);
		frc::Scheduler::GetInstance()->Run();
		/*frc::SmartDashboard::PutNumber("Encoder", shooter->getEncoderVel());
		 shooter->setPIDConstants(1, 1, 0, 0);
		 shooter->setSpeed(15000);
		 std::cout << "Speed: " << shooter->getSpeed() << std::endl;
		 std::cout << "shooter found" << std::endl;
		 */
		std::cout << "Winch Current " << CommandBase::winch->getCurrent()
				<< std::endl;
		frc::SmartDashboard::PutNumber("CANTalon 1 Current",
				CommandBase::winch->getCurrent());
		frc::SmartDashboard::PutNumber("Gyro",
				CommandBase::drive->getGyroAngle());
		frc::SmartDashboard::PutNumber("EncoderTest",
				CommandBase::drive->getLeftEncoderDistance());
		frc::SmartDashboard::PutNumber("EncoderRight",
				CommandBase::drive->getRightEncoderDistance());
		frc::SmartDashboard::PutBoolean("CVGearFound",
				NetworkTablesInterface::gearFound());
		frc::SmartDashboard::PutNumber("CVGearDistance",
				NetworkTablesInterface::getGearDistance());
		frc::SmartDashboard::PutNumber("CVGearAltitude",
				NetworkTablesInterface::getGearAltitude());
		frc::SmartDashboard::PutNumber("CVGearAzimuth",
				NetworkTablesInterface::getGearAzimuth());

	}

	void TestInit() override
	{
		CommandBase::winch->getCurrent();
		Command* autonomousCommand;

	}

	void TestPeriodic() override
	{
		frc::Scheduler::GetInstance()->Run();
		CommandBase::drive->gyro->periodicProcessing(startupTime);
		frc::SmartDashboard::PutBoolean("CVGearFound",
				NetworkTablesInterface::gearFound());
		frc::SmartDashboard::PutNumber("CVGearDistance",
				NetworkTablesInterface::getGearDistance());
		frc::SmartDashboard::PutNumber("CVGearAltitude",
				NetworkTablesInterface::getGearAltitude());
		frc::SmartDashboard::PutNumber("CVGearAzimuth",
				NetworkTablesInterface::getGearAzimuth());
		frc::SmartDashboard::PutBoolean("CVBoilerFound",
				NetworkTablesInterface::boilerFound());
		frc::SmartDashboard::PutNumber("CVBoilerDistance",
				NetworkTablesInterface::getBoilerDistance());
		frc::SmartDashboard::PutNumber("CVBoilerAltitude",
				NetworkTablesInterface::getBoilerAltitude());
		frc::SmartDashboard::PutNumber("CVBoilerAzimuth",
				NetworkTablesInterface::getBoilerAzimuth());
		frc::LiveWindow::GetInstance()->Run();
	}

private:
	CommandGroup* autonomousCommand;
	//CommandGroup* drivingCommand;
	frc::SendableChooser<frc::Command*> chooser;
	//Command* foreward;
	//Talon* left;
	//Talon* right;
};

START_ROBOT_CLASS(Robot)
