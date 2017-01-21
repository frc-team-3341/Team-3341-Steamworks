/*
 * GyroL3GD20H.h
 *
 *  Created on: Oct 29, 2016
 *      Author: nidhi
 */

#ifndef GYROL3GD20H_H_
#define GYROL3GD20H_H_
#include "I2C.h"
#include "GyroAxis.h"

namespace wvrobotics {

class GyroL3GD20H {
	enum State {
		UNCONNECTED = 0,
		CALIBRATING = 1,
		CONNECTED
	};

    typedef enum
    {
      GYRO_RANGE_250DPS  = 250,
      GYRO_RANGE_500DPS  = 500,
      GYRO_RANGE_2000DPS = 2000
    } gyroRange_t;

    enum Autoincrement: unsigned char
	{
    	AUTO_INCREMENT = 0x80
	};

    enum FIFOsource: unsigned char
	{
    	FIFOSOURCE_OVERRUN = 0x40,
    	FIFOSOURCE_EMPTY = 0x20,
		FIFOSOURCE_DATA_SAMPLES = 0x1F
	};

    enum Gyrostatus: unsigned char
	{
    	ZYXOR = 0x80,
    	ZYXDA = 0x08
	};
    enum FIFOcontrol: unsigned char //values for FIFO control register as detailed on page 42 of the spec
	{
    	FIFO_BYPASS_MODE         = 0x00,
		FIFO_DYNAMIC_STREAM_MODE = 0xC0

	};
    typedef enum
    {                                             // DEFAULT    TYPE
        GYRO_REGISTER_WHO_AM_I            = 0x0F,   // 11010100   r
        GYRO_REGISTER_CTRL_REG1           = 0x20,   // 00000111   rw
        GYRO_REGISTER_CTRL_REG2           = 0x21,   // 00000000   rw
        GYRO_REGISTER_CTRL_REG3           = 0x22,   // 00000000   rw
        GYRO_REGISTER_CTRL_REG4           = 0x23,   // 00000000   rw
        GYRO_REGISTER_CTRL_REG5           = 0x24,   // 00000000   rw
        GYRO_REGISTER_REFERENCE           = 0x25,   // 00000000   rw
        GYRO_REGISTER_OUT_TEMP            = 0x26,   //            r
        GYRO_REGISTER_STATUS_REG          = 0x27,   //            r
        GYRO_REGISTER_OUT_X_L             = 0x28,   //            r
        GYRO_REGISTER_OUT_X_H             = 0x29,   //            r
        GYRO_REGISTER_OUT_Y_L             = 0x2A,   //            r
        GYRO_REGISTER_OUT_Y_H             = 0x2B,   //            r
        GYRO_REGISTER_OUT_Z_L             = 0x2C,   //            r
        GYRO_REGISTER_OUT_Z_H             = 0x2D,   //            r
        GYRO_REGISTER_FIFO_CTRL_REG       = 0x2E,   // 00000000   rw
        GYRO_REGISTER_FIFO_SRC_REG        = 0x2F,   //            r
        GYRO_REGISTER_INT1_CFG            = 0x30,   // 00000000   rw
        GYRO_REGISTER_INT1_SRC            = 0x31,   //            r
        GYRO_REGISTER_TSH_XH              = 0x32,   // 00000000   rw
        GYRO_REGISTER_TSH_XL              = 0x33,   // 00000000   rw
        GYRO_REGISTER_TSH_YH              = 0x34,   // 00000000   rw
        GYRO_REGISTER_TSH_YL              = 0x35,   // 00000000   rw
        GYRO_REGISTER_TSH_ZH              = 0x36,   // 00000000   rw
        GYRO_REGISTER_TSH_ZL              = 0x37,   // 00000000   rw
        GYRO_REGISTER_INT1_DURATION       = 0x38    // 00000000   rw
      } gyroRegisters_t;


    enum
	{

		L3GD20_ADDRESS = 0x6B,      // 1101011
		L3GD20_POLL_TIMEOUT = (100),         // Maximum number of read attempts
		//L3GD20_ID = 0xD4,
		L3GD20H_ID = 0xD7
	};


    static constexpr double GYRO_SENSITIVITY_250DPS  = 0.00875;  // Roughly 22/256 for fixed point match
    static constexpr double GYRO_SENSITIVITY_500DPS  = 0.0175;    // Roughly 45/256
    static constexpr double GYRO_SENSITIVITY_2000DPS = 0.070;      // Roughly 18/256

private:
	State mState;
	I2C m_i2c;
	int overrunGyroCount;
	int xCalibration;
	int yCalibration;
	int zCalibration;
	int calibrationCount;
	int xCalibrateTotal;
	int yCalibrateTotal;
	int zCalibrateTotal;
	int count;
	GyroAxis sum;
	double conversionFactor = 0;

public:
	GyroL3GD20H(I2C::Port port, int deviceAddress);
	virtual ~GyroL3GD20H();
	void initializeGyro();
	void readGyroData();
	void resetGyro()
	{
		sum.setAxis(0,0,0);
		count = 0;
	}
	void getAngle(GyroAxis* pAxis)
	{
		*pAxis = sum;
	}
	int getCount()
	{
		return count;
	}


	//void InitTable(std::shared_ptr<ITable> subtable);
	//void UpdateTable();


};

} /* namespace wvrobotics */

#endif /* GYROL3GD20H_H_ */
