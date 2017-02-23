/*
 * NewGyro.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: nidhi
 */

#include "NewGyro.h"
#include <iostream>
//#include "HAL/HAL.h"
//#include "LiveWindow/LiveWindow.h"
using namespace frc;
using namespace std::chrono_literals;
//constexpr double kGsPerLSB;

/**
 * Constructs the ADXL345 Accelerometer over I2C.
 *
 *By Deepali Jain
 *
 * @param port          The I2C port the accelerometer is attached to
 * @param range         The range (+ or -) that the accelerometer will measure
 * @param deviceAddress The I2C address of the accelerometer (0x1D or 0x53)
 */

namespace wvrobotics {

NewGyro::NewGyro(I2C::Port port, int deviceAddress)
    : m_i2c(port, deviceAddress) {

	m_i2c.Write(GYRO_REGISTER_CTRL_REG1, 0x0F);

	//float zAxisArray[10] = {};
	//float avg = 0;
	count = 0;
	calibrationcount = 0;
	sum.setAxis(0,0,0);
	mState = UNCONNECTED;
	overrunGyroCount = 0;
	isVerified = m_i2c.VerifySensor(ADDRESS, 1, &whoAmI);
	if(isVerified)
		mState = INITIALIZATION;
	std::cout << "locate sensor: "<< (int)isVerified << std::endl;
	clock_initial = std::clock();
	t_start = std::chrono::high_resolution_clock::now();
	clock_gyro = std::clock();
	 m_i2c.Write(GYRO_REGISTER_CTRL_REG1, 0x00);

	//if(isVerified)
		//mState = CALIBRATING;

	std::cout << "gyro state " << mState << std::endl;
/*
  HAL_Report(HALUsageReporting::kResourceType_ADXL345,
             HALUsageReporting::kADXL345_I2C, 0);
  LiveWindow::GetInstance()->AddSensor("ADXL345_I2")
  */
}

NewGyro::~NewGyro() {
	// TODO Auto-generated destructor stub
}

void NewGyro::periodicProcessing(int startupTime)
{
	isVerified = m_i2c.VerifySensor(ADDRESS, 1, &whoAmI);
		if(isVerified == false)
		{
			mState=UNCONNECTED;
			//std::cout << "gyro state " << mState << std::endl;
		}
		//subtract gyro clock from robot clock and if it is more than a set time set mstate=calibration

		std::chrono::high_resolution_clock::time_point t_end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span;
		switch(mState)
		{
			case UNCONNECTED:
				std::cout << "Your gyro is not connected."<< std::endl;
				break;
			case INITIALIZATION:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_start);
				//std::cout << "It took me " << time_span.count() << " seconds" << std::endl;
				//timeDiff = clock_initial - clock_gyro;
				//std::cout << "time difference: " << timeDiff << std::endl;
				if(time_span.count() > startupTime)
				{
					initializeGyro();
					mState = CALIBRATING;
					//std::cout << "gyro state " << mState << std::endl;
				}
				break;
			case CALIBRATING:
				readGyroData();
				if(TOTAL_COUNT < count)
				{
					//avg = sum.getzAxis()/count;
					sum.setAxis(0,0,0);
					count = 0;
					mState = READY;
					//std::cout << "gyro state " << mState << std::endl;
				}
				break;
			case READY:
				int temp = count;
				readGyroData();
				int totalCount = count - temp;
				if(totalCount > 0)
				{
					sum.overrunofAxis();
					sum.setzAxis(sum.getzAxis() - (double)(avg*totalCount));
					//std::cout << "Gyro z axis: " << (sum.getzAxis() - (double)(avg*totalCount)) << std::endl;
				}
		// determine the number of new samples read
		// if there is new data, subtract out the calibration value multiplied by the number of new samples from the data
				break;
		}
}


void NewGyro::initializeGyro()
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

	  //std::this_thread::sleep_for(2s);
	  //gyroFinal = std::chrono::high_resolution_clock::now();
	  //std::chrono::duration<double> time_span;
	  //time_span = std::chrono::duration_cast<std::chrono::duration<double>>(gyroFinal - t_start);
	// m_i2c.Write(GYRO_REGISTER_CTRL_REG1, 0x00);
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

GyroAxis* NewGyro::getAxis()
{
	return &sum;
}

GyroAxis NewGyro::readGyroData() //read gyro status, read FIFO source, read GYRO_REGISTER_OUT_X_L
{
	short data[3];
	uint8_t registerVal;
	unsigned char status = 0;
	uint8_t dataAvailable;
	uint8_t discardedData[6];
	uint8_t *byteData = (uint8_t*)data;
	m_i2c.Read(GYRO_REGISTER_STATUS_REG, 1, &status);
	//std::cout << "Status of gyro: " << std::hex << (int)status << std::dec << std::endl;


	if(status & ZYXDA) // check for data available
	{
		m_i2c.Read(GYRO_REGISTER_FIFO_SRC_REG, 1, &registerVal);
		//std::cout << "FIFO Source Register: " << std::hex << (int)registerVal << std::dec  << std::endl;

		if(FIFOSOURCE_OVERRUN & registerVal)
		{
			overrunGyroCount++;
			std::cout << "Gyro overrun: " << overrunGyroCount << std::endl;
		}

		dataAvailable = (registerVal & FIFOSOURCE_DATA_SAMPLES) + 1;
		for(int i = 0; i < dataAvailable; i++ )
		{
			//m_i2c.Read(GYRO_REGISTER_OUT_X_L | AUTO_INCREMENT, 6, (uint8_t*)data);

		    m_i2c.Read(GYRO_REGISTER_OUT_X_L, 1, byteData);
		    m_i2c.Read(GYRO_REGISTER_OUT_X_H, 1, byteData + 1);
		    m_i2c.Read(GYRO_REGISTER_OUT_Y_L, 1, byteData + 2);
		    m_i2c.Read(GYRO_REGISTER_OUT_Y_H, 1, byteData + 3);
		    m_i2c.Read(GYRO_REGISTER_OUT_Z_L, 1, byteData + 4);
		    m_i2c.Read(GYRO_REGISTER_OUT_Z_H, 1, byteData + 5);


		    m_i2c.Read(GYRO_REGISTER_OUT_X_L | AUTO_INCREMENT, 6, discardedData);
			sum.addAxis(data[0]*conversionFactor, data[1]*conversionFactor, data[2]*conversionFactor);
			count++;
			//std::cout << "Gyro ACTUAL data: " << std::hex << data[2] <<  std::dec << std::endl;

		}

	}
return sum;
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
