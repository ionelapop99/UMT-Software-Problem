#include "pch.h"
#include "meeting.h"
#include <cstring>
#include <iostream>

using namespace std;


meeting::meeting()
{
	this->start_hour = "00:00";
	this->finish_hour = "00:00";
}

meeting::meeting(string startHour,string stopHour)
{
	this->start_hour =startHour;
	this->finish_hour = stopHour;
}


meeting::~meeting()
{

}
//--------------------------------------------------------------
//Getters
string meeting::getStart_hour()
{
	return this->start_hour;
}
string meeting::getFinish_hour()
{
	return this->finish_hour;
}

//--------------------------------------------------------------
//Setters
void meeting::setStart_hour(string startHour)
{
	this->start_hour = startHour;
}
void meeting::setFinish_hour(string finishHour)
{
	this->finish_hour = finishHour;
}
//------------------------------------------------------

