#include <math.h>

#include "../RobotMap.h"
#include "../CommandBase.h"
#include "../Commands/TankDrive.h"

#include "DriveTrain.h"

#define max(x, y) (((x) > (y)) ? (x) : (y))

DriveTrain::DriveTrain() :
    Subsystem("DriveTrain"), left(new Talon(0)), right(new Talon(1)),
    encoderLeft(new Encoder(ENCODER_LEFT_1, ENCODER_LEFT_2)),
    encoderRight(new Encoder(ENCODER_RIGHT_1, ENCODER_RIGHT_2)), mult(1.0),
	ticksToDistance(114), // 112 < ticksToDistance < 117
	accel(),
	gyro(new wvrobotics::GyroL3GD20H(I2C::kOnboard, 0x6b))//wvrobotic::GyroL3GD20H( wvrobotics::GyroL3GD20H::GyroL3GD20H))//,
	//ultrasonicSensors()
{
    encoderLeft->SetDistancePerPulse(1.0);
    encoderRight->SetDistancePerPulse(1.0);

    //gyro->Calibrate();
    //gyro->Reset();
}


DriveTrain::~DriveTrain()
{
    delete left;
    delete right;
    delete encoderLeft;
    delete encoderRight;
    //delete accel;
    delete gyro;
}

void DriveTrain::setMult(float m)
{
    mult = m;
}

int DriveTrain::getMult()
{
	return mult;
}

void DriveTrain::resetEncoders()
{
    encoderLeft->Reset();
    encoderRight->Reset();
}

void DriveTrain::arcadeDrive(float moveValue, float rotateValue)
{
    float leftMotorOutput;
    float rightMotorOutput;

    moveValue = DriveTrain::Limit(moveValue, 1.0) * mult;
    rotateValue = -DriveTrain::Limit(rotateValue, 1.0);

    // Standard ArcadeDriveTrain algorithm from Google
    if(moveValue > 0.0)
    {
        if(rotateValue > 0.0)
        {
            leftMotorOutput = moveValue - rotateValue;
            rightMotorOutput = max(moveValue, rotateValue);
        }
        else
        {
            leftMotorOutput = max(moveValue, -rotateValue);
            rightMotorOutput = moveValue + rotateValue;
        }
    }
    else
    {
        if(rotateValue > 0.0)
        {
            leftMotorOutput = - max(-moveValue, rotateValue);
            rightMotorOutput = moveValue + rotateValue;
        }
        else
        {
            leftMotorOutput = moveValue - rotateValue;
            rightMotorOutput = - max(-moveValue, -rotateValue);
        }
    }

    float limitedL = DriveTrain::Limit(leftMotorOutput, 1.0);
    float limitedR = -DriveTrain::Limit(rightMotorOutput, 1.0);

    left->Set(-limitedL);
    right->Set(-limitedR);
}

void DriveTrain::tankDrive(float moveValueLeft, float moveValueRight)
{
    //float leftMotorOutput;
    //float rightMotorOutput;

    moveValueLeft = DriveTrain::Limit(moveValueLeft, 1.0);
    moveValueRight = -DriveTrain::Limit(moveValueRight, 1.0);

    //std::cout << "LeftRaw: " << limitedL<< "\n";
	//std::cout << "RightRaw: " << limitedR << "\n";
    // TODO: mult should never be 0, but robot wasn't driving for some reason
    if (mult != 0) {
		left->Set(-moveValueLeft);
		right->Set(-moveValueRight);
    }
    else {
    	left->Set(-moveValueLeft);
		right->Set(-moveValueRight);
    }
}

float DriveTrain::Limit(float num, float max)
{
    if(num > max)
        return max;

    if(num < -max)
        return -max;

    return num;
}

// Return distance in feet
double DriveTrain::getDistance()
{
    // Average of both encoders (must negate to get proper direction)
    return
    (
        (double) ((encoderLeft->Get()) / ticksToDistance) -
        (double) ((encoderRight->Get()) / ticksToDistance)
    ) / -2.0;
}

double DriveTrain::getRate()
{
    // Average of both encoder rates (must negate to get proper direction)
    // TODO: test to see if negation is necessary
    return
    (
        (double) ((encoderLeft->GetRate()) / ticksToDistance) -
        (double) ((encoderRight->GetRate()) / ticksToDistance)
    ) / -2.0;

}

void DriveTrain::getAccelerations(double* x, double* y, double* z)
{
	//*x = accel->GetX();
	//*y = accel->GetY();
	//*z = accel->GetZ();
}

void DriveTrain::InitDefaultCommand()
{
    SetDefaultCommand(new TankDrive());
}


double DriveTrain::getLeftEncoderDistance()
{
	//return this->left->GetPosition();
	return this->encoderLeft->GetDistance();
}

double DriveTrain::getRightEncoderDistance()
{
	return -this->encoderRight->GetDistance();
}

double DriveTrain::getGyroAngle()
{
	wvrobotics::GyroAxis axis;
    gyro->getAngle(&axis);
    axis.overrunofAxis();
    return axis.getzAxis();
}

void DriveTrain::resetGyro()
{
    gyro->resetGyro();
}

double DriveTrain::readUltra(uint16_t sensorIndex)
{
	return 0.0;//ultrasonicSensors->ReadUltra(sensorIndex);
}

void DriveTrain::setSpeedLeft(double speed){
	left->SetSpeed(speed);
}

void DriveTrain::setSpeedRight(double speed){
	right->SetSpeed(speed);
}
