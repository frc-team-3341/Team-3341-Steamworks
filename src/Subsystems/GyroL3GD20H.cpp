/*
 * GyroL3GD20H.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: nidhi
 */

#include "GyroL3GD20H.h"
#include <iostream>
//#include "HAL/HAL.h"
//#include "LiveWindow/LiveWindow.h"


//constexpr double kGsPerLSB;

/**
 * Constructs the ADXL345 Accelerometer over I2C.
 *
 * @param port          The I2C port the accelerometer is attached to
 * @param range         The range (+ or -) that the accelerometer will measure
 * @param deviceAddress The I2C address of the accelerometer (0x1D or 0x53)
 */

namespace wvrobotics {

GyroL3GD20H::GyroL3GD20H(I2C::Port port, int deviceAddress)
    : m_i2c(port, deviceAddress) {

	m_i2c.Write(GYRO_REGISTER_CTRL_REG1, 0x0F);

	xCalibration = 0;
	yCalibration = 0;
	zCalibration = 0;
	count = 0;
	calibrationCount = 0;
	sum.setAxis(0,0,0);
	mState = UNCONNECTED;
	const unsigned char ADDRESS = 0xF;
	unsigned char whoAmI = 0b11010111;
	overrunGyroCount = 0;
	bool isVerified = m_i2c.VerifySensor(ADDRESS, 1, &whoAmI);
	std::cout << "locate sensor: "<< (int)isVerified << std::endl;
	if(isVerified)
		mState = CALIBRATING;

/*
  HAL_Report(HALUsageReporting::kResourceType_ADXL345,
             HALUsageReporting::kADXL345_I2C, 0);
  LiveWindow::GetInstance()->AddSensor("ADXL345_I2")
  */
}

GyroL3GD20H::~GyroL3GD20H() {
	// TODO Auto-generated destructor stub
}


void GyroL3GD20H::initializeGyro()
{
	  /* Set CTRL_REG1 (0x20)
	   ====================================================================
	   BIT  Symbol    Description                                   Default
	   ---  ------    --------------------------------------------- -------
	   7-6  DR1/0     Output data rate                                   00
	   5-4  BW1/0     Bandwidth selection                                00
	     3  PD        0 = Power-down mode, 1 = normal/sleep mode          0
	     2  ZEN       Z-axis enable (0 = disabled, 1 = enabled)           1
	     1  YEN       Y-axis enable (0 = disabled, 1 = enabled)           1
	     0  XEN       X-axis enable (0 = disabled, 1 = enabled)           1 */

	  /* Reset then switch to normal mode and enable all three channels */
	double dataRate = 94.7;
	  m_i2c.Write(GYRO_REGISTER_CTRL_REG1, 0x00);
	  m_i2c.Write(GYRO_REGISTER_CTRL_REG1, 0x0F);
	  /* ------------------------------------------------------------------ */

	  /* Set CTRL_REG2 (0x21)
	   ====================================================================
	   BIT  Symbol    Description                                   Default
	   ---  ------    --------------------------------------------- -------
	   5-4  HPM1/0    High-pass filter mode selection                    00
	   3-0  HPCF3..0  High-pass filter cutoff frequency selection      0000 */

	  /* Nothing to do ... keep default values */
	  /* ------------------------------------------------------------------ */

	  /* Set CTRL_REG3 (0x22)
	   ====================================================================
	   BIT  Symbol    Description                                   Default
	   ---  ------    --------------------------------------------- -------
	     7  I1_Int1   Interrupt enable on INT1 (0=disable,1=enable)       0
	     6  I1_Boot   Boot status on INT1 (0=disable,1=enable)            0
	     5  H-Lactive Interrupt active config on INT1 (0=high,1=low)      0
	     4  PP_OD     Push-Pull/Open-Drain (0=PP, 1=OD)                   0
	     3  I2_DRDY   Data ready on DRDY/INT2 (0=disable,1=enable)        0
	     2  I2_WTM    FIFO wtrmrk int on DRDY/INT2 (0=dsbl,1=enbl)        0
	     1  I2_ORun   FIFO overrun int on DRDY/INT2 (0=dsbl,1=enbl)       0
	     0  I2_Empty  FIFI empty int on DRDY/INT2 (0=dsbl,1=enbl)         0 */

	  /* Nothing to do ... keep default values */
	  /* ------------------------------------------------------------------ */

	  /* Set CTRL_REG4 (0x23)
	   ====================================================================
	   BIT  Symbol    Description                                   Default
	   ---  ------    --------------------------------------------- -------
	     7  BDU       Block Data Update (0=continuous, 1=LSB/MSB)         0
	     6  BLE       Big/Little-Endian (0=Data LSB, 1=Data MSB)          0
	   5-4  FS1/0     Full scale selection                               00
	                                  00 = 250 dps
	                                  01 = 500 dps
	                                  10 = 2000 dps
	                                  11 = 2000 dps
	     0  SIM       SPI Mode (0=4-wire, 1=3-wire)                       0 */

	  /* Adjust resolution if requested */
	  auto range = GYRO_RANGE_500DPS;
	  switch(range)
	  {
	    case GYRO_RANGE_250DPS:
	    	m_i2c.Write(GYRO_REGISTER_CTRL_REG4, 0x00);
	    	conversionFactor = GYRO_SENSITIVITY_250DPS/dataRate;
	      break;
	    case GYRO_RANGE_500DPS:
	    	m_i2c.Write(GYRO_REGISTER_CTRL_REG4, 0x10);
	    	conversionFactor = GYRO_SENSITIVITY_500DPS/dataRate;
	      break;
	    case GYRO_RANGE_2000DPS:
	    	m_i2c.Write(GYRO_REGISTER_CTRL_REG4, 0x20);
	    	conversionFactor = GYRO_SENSITIVITY_2000DPS/dataRate;
	      break;
	  }
	  /* ------------------------------------------------------------------ */

	  /* Set CTRL_REG5 (0x24)
	   ====================================================================
	   BIT  Symbol    Description                                   Default
	   ---  ------    --------------------------------------------- -------
	     7  BOOT      Reboot memory content (0=normal, 1=reboot)          0
	     6  FIFO_EN   FIFO enable (0=FIFO disable, 1=enable)              0
	     4  HPen      High-pass filter enable (0=disable,1=enable)        0
	   3-2  INT1_SEL  INT1 Selection config                              00
	   1-0  OUT_SEL   Out selection config                               00 */

	  /* Nothing to do ... keep default values */
	  /* ------------------------------------------------------------------ */

	  //return true;

	  m_i2c.Write(GYRO_REGISTER_CTRL_REG5, 0b01000000);

	  //m_i2c.Write(GYRO_REGISTER_FIFO_CTRL_REG, FIFO_BYPASS_MODE);
	  m_i2c.Write(GYRO_REGISTER_FIFO_CTRL_REG, FIFO_DYNAMIC_STREAM_MODE | 30); //set the FIFO size to 30 as detailed on page 22 of the spec

}



void GyroL3GD20H::readGyroData() //read gyro status, read FIFO source, read GYRO_REGISTER_OUT_X_L
{
	short data[3];
	uint8_t registerVal;
	unsigned char status = 0;
	uint8_t dataAvailable;
	m_i2c.Read(GYRO_REGISTER_STATUS_REG, 1, &status);
	std::cout << "Status of gyro: " << std::hex << (int)status << std::dec << std::endl;

	//xCalibration = xCalibrateTotal/calibrationCount;
	//yCalibration = yCalibrateTotal/calibrationCount;
	//zCalibration = zCalibrateTotal/calibrationCount;

	if(status & ZYXDA) // check for data available
	{
		m_i2c.Read(GYRO_REGISTER_FIFO_SRC_REG, 1, &registerVal);
		std::cout << "FIFO Source Register: " << std::hex << (int)registerVal << std::dec  << std::endl;

		if(FIFOSOURCE_OVERRUN & registerVal)
		{
			overrunGyroCount++;
			std::cout << "Gyro overrun: " << overrunGyroCount << std::endl;
		}

		dataAvailable = (registerVal & FIFOSOURCE_DATA_SAMPLES) + 1;

		for(int i = 0; i < dataAvailable; i++ )
		{
			m_i2c.Read(GYRO_REGISTER_OUT_X_L | AUTO_INCREMENT, 6, (uint8_t*)data);
			//std::cout << "Gyro sample data: " << (data[0]) << ", " << (data[1]) << ", " << (data[2]) << std::endl;
			sum.addAxis(data[0]*conversionFactor, data[1]*conversionFactor, data[2]*conversionFactor);
			std::cout << "Gyro sum : " << sum.getxAxis()  << ", " << sum.getyAxis() << ", " << sum.getzAxis() << std::endl;
			count++;
		}

	}

}


/**
 * Get the acceleration of one axis in Gs.
 *
 * @param axis The axis to read from.
 * @return Acceleration of the ADXL345 in Gs.
 */


/**
 * Get the acceleration of all axes in Gs.
 *
 * @return An object containing the acceleration measured on each axis of the
 *         ADXL345 in Gs.
 */

/**
void ADXL345_I2C::InitTable(std::shared_ptr<ITable> subtable) {
  m_table = subtable;
  UpdateTable();
}
void ADXL345_I2C::UpdateTable() {
  m_table->PutNumber("X", GetX());
  m_table->PutNumber("Y", GetY());
  m_table->PutNumber("Z", GetZ());
}
std::shared_ptr<ITable> ADXL345_I2C::GetTable() const { return m_table; }**/


} /* namespace wvrobotics */
