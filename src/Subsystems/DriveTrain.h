#ifndef DriveTrain_H
#define DriveTrain_H

#include <WPILib.h>
#include "Commands/Subsystem.h"
//#include "../Sensors/UltrasonicSensors.h"
#include "Subsystems/GyroL3GD20H.h"
#include "Subsystems/GyroAxis.h"
//using namespace frc;
class DriveTrain: public Subsystem
{
    private:



        Talon* left;
        Talon* right;
        Encoder* encoderLeft;
        Encoder* encoderRight;
        float mult;
        int ticksToDistance;
        BuiltInAccelerometer* accel;
        wvrobotics::GyroL3GD20H* gyro;
        //DigitalGyro* gyro;
        //UltrasonicSensors* ultrasonicSensors;

    public:
        DriveTrain();
        ~DriveTrain();

        static float Limit(float num, float max);

        void setMult(float m);
        int getMult();
        void arcadeDrive(float move, float rotate);
        void tankDrive(float moveValueLeft, float moveValueRight);

        double getDistance();
        double getRate();
        void resetEncoders();
        void getAccelerations(double* x, double* y, double* z);

        double getRightEncoderDistance();
        double getLeftEncoderDistance();

        double getGyroAngle();
        void resetGyro();

        double readUltra(uint16_t sensorIndex);

        void setSpeedLeft(double speed);
        void setSpeedRight(double speed);   //if needed

        void InitDefaultCommand();
};

#endif

