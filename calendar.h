#pragma once
#include "pch.h"
#include <iostream>
#include "meeting.h"
#include<vector>

using namespace std;

#ifndef CALENDAR_H
#define CALENDAR_H
class calendar
{ 
private:
	string range_min, range_max;
	vector<meeting> booked;

public:
	calendar();
	calendar(string, string, const vector<meeting>&v);
	~calendar();

	//--------------------------------------------------------------
	//Getters
	string getRange_min();
	string getRange_max();

	//--------------------------------------------------------------
	//Setters
	void setRange_min(string);
	void setRange_max(string);
	void setBooked(const vector<meeting> &b);
	//----------------------------------------------------------------
	meeting* getAllBooked();
    int getSizeBooked();
	void sort_calendar();
};
#endif;
