#pragma once
#include "pch.h"
#include <iostream>

using namespace std;

#ifndef MEETING_H
#define MEETING_H
class meeting
{
private:
	string start_hour, finish_hour;
public:
	meeting();
	meeting(string, string);
	~meeting();
	//--------------------------------------------------------------
	//Getters
	string getStart_hour();
	string getFinish_hour();

	//--------------------------------------------------------------
	//Setters
	void setStart_hour(string);
	void setFinish_hour(string);
	//---------------------------------------------------------------
	
};
#endif;
