/*
 * NetworkTablesInterface.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: Dhruti
 */

#include "NetworkTablesInterface.h"


/*NetworkTablesInterface::NetworkTablesInterface() {
	// TODO Auto-generated constructor stub

}

NetworkTablesInterface::~NetworkTablesInterface() {
	// TODO Auto-generated destructor stub
}*/

bool NetworkTablesInterface::gearFound(){
	return NetworkTable::GetTable("cv")->GetBoolean("gearFound", false);
	//returns true if the gear has been detected
}

double NetworkTablesInterface::getGearDistance()
{
	return NetworkTable::GetTable("cv")->GetNumber("gearDistance", -1.0);
}

double NetworkTablesInterface::getGearAltitude()
{
	return NetworkTable::GetTable("cv")->GetNumber("gearAltitude", -1.0);
}

double NetworkTablesInterface::getGearAzimuth()
{
	return NetworkTable::GetTable("cv")->GetNumber("gearAzimuth", -1.0);
}
bool NetworkTablesInterface::boilerFound()
{
	return NetworkTable::GetTable("cv")->GetBoolean("boilerFound", false);
}

double NetworkTablesInterface::getBoilerDistance()
{
	return NetworkTable::GetTable("cv")->GetNumber("boilerDistance", -1.0);
}

double NetworkTablesInterface::getBoilerAltitude()
{
	return NetworkTable::GetTable("cv")->GetNumber("boilerAltitude", -1.0);
}

double NetworkTablesInterface::getBoilerAzimuth()
{
	return NetworkTable::GetTable("cv")->GetNumber("boilerAzimuth", -1.0);
}
