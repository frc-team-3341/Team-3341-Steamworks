/*
 * GyroAxis.h
 *
 *  Created on: Dec 6, 2016
 *      Author: nidhi
 */

#ifndef GYROAXIS_H_
#define GYROAXIS_H_
#include <iostream>
#include <math.h>

namespace wvrobotics {

class GyroAxis {

private:
	double xAxis;
	double yAxis;
	double zAxis;
	float zAxisArray[];
	float sum;
	float avg = 0;
public:
	GyroAxis();
	double getxAxis()
	{
		return xAxis;
	}
	double getyAxis()
	{
		return yAxis;
	}
	double getzAxis()
	{
		return zAxis;
	}
	void setxAxis(double x)
	{
		xAxis = x;
	}
	void setyAxis(double y)
	{
		yAxis = y;
	}
	void setzAxis(double z)
	{
		zAxis = z;
	}
	void setAxis(double x, double y, double z)
	{
		xAxis = x;
		yAxis = y;
		zAxis = z;
	}
	void addAxis(double x, double y, double z)
	{
		xAxis += x;
		yAxis += y;
		zAxis += z;
	}

	float checkForZAxis(int counterGyro)
		{
			if (counterGyro<10)
			{
			   //add data to the array
			   zAxisArray[counterGyro]=zAxis;
			   counterGyro++;
			   std::cout << "zAXis: " << zAxis  <<  std::endl;
			   std::cout << "Counter: " << counterGyro  <<  std::endl;
			}
			else if (counterGyro==10)//find average
			{

			  for(int i = 1; i <=10 ; i++){
				   sum += zAxisArray[i];
				}
				avg = sum / 10;
				counterGyro++;
				std::cout << "Counter REACHED 10: " << counterGyro  <<  std::endl;
			}
			else if(counterGyro>10)
			{
				std::cout << "zAXis average : " << avg-zAxis  <<  std::endl;
				counterGyro++;
				std::cout << "Counter OVER 10: " << counterGyro  <<  std::endl;
				counterGyro = 0;
			}

			return avg;

		}

	void overrunofAxis()
	 	{
			xAxis = fmod(xAxis, 360);
	 		//xAxis = (int)xAxis % 360;
	 		if(xAxis > 180)
	 		{
	 			xAxis -= 360;
	 		}
	 		else if(xAxis < -180)
	 		{
	 			xAxis += 360;
	 		}

	 		zAxis = fmod(zAxis, 360);
	 		//zAxis = (int)zAxis%360;
	 		if(zAxis > 180)
	 		{
	 			zAxis -= 360;
	 		}
	 		else if(zAxis < -180)
	 		{
	 			zAxis += 360;
	 		}

	 		yAxis = fmod(yAxis, 360);
	 		//yAxis = (int)yAxis%360;
	 		if(yAxis > 180)
	 		{
	 			yAxis -= 360;
	 		}
	 		else if(yAxis < -180)
	 		{
	 			yAxis += 360;
	 		}

	 	}
	~GyroAxis();
};

} /* namespace wvrobotics */

#endif /* GYROAXIS_H_ */
