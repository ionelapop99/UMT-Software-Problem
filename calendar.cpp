#include "pch.h"
#include "calendar.h"
#include <algorithm>  
#include<string>

using namespace std;

calendar::calendar()
{
	this->range_min = "00:00";
	this->range_max = "00:00";
	this->booked.reserve(30);
}

calendar::calendar(string range_min, string range_max, const vector<meeting> &v)
{
	this->range_min = range_min;
	this->range_max = range_max;
	for (unsigned i = 0; i < v.size(); i++) {
		this->booked.push_back(v[i]);
	}
}


calendar::~calendar()
{
	this->booked.~vector();
}
//--------------------------------------------------------------
//Getters
string calendar::getRange_min()
{
	return this->range_min;
}

string calendar::getRange_max()
{
	return this->range_max;
}

int calendar::getSizeBooked()
{
	return this->booked.size();
}

meeting* calendar::getAllBooked()
{
	return &this->booked[0]; 
}

//--------------------------------------------------------------
//Setters
void calendar::setRange_min( string range_min)
{
	this->range_min = range_min;
}

void calendar::setRange_max(string range_max)
{
	this->range_max = range_max;
}

void calendar::setBooked(const vector<meeting> &v)
{
	for (unsigned i = 0; i < v.size(); i++) {
		this->booked.push_back(v[i]);
	}
}

//-----------------------------------------------------------------
//Descriere: functia verifica daca stringul s1 este mai mic decat stringul s2
//			in caz afirmativ returneaza true, altfel returneaza false
//input: s1,s2-stringuri de exemplu "09:00"
//output:
//-----------------------------------------------------------------
bool maimic(string s1, string s2)
{
	string ora1="", ora2="", min1="", min2="";
	//ora1 este ora aferenta primului string si
	//e obtinuta prin concatenarea caracterului de pe pozitia 0 cu caracterul de pe pozitia 1
	ora1 += s1[0];
	ora1 += s1[1];
	//ora2 este ora aferenta celui de-al doilea string
	//e obtinuta prin concatenarea caracterului de pe pozitia 0 cu caracterul de pe pozitia 1
	ora2 += s2[0];
	ora2 += s2[1];

	//pe pozitia 2 avem ":"

	//min1 sunt minutele aferente stringului 1
	min1 += s1[3];
	min1 += s1[4];
	
	//min2 sunt minutele aferente stringului 2
	min2 += s2[3];
	min2 += s2[4];
	
	if (ora1 < ora2)
	{
		return true;
	}
	else
	{
		if (ora1 == ora2)
		{
			if (min1 < min2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}
//-----------------------------------------------------------------
//Descriere: functia sorteaza meetingurile din calendar atat dupa orele de inceput cat si dupa orele de sfarsit
//input: meeting &m1, meeting &m2
//output:-
//-----------------------------------------------------------------
void calendar::sort_calendar()
{
	sort(booked.begin(), booked.end(), [](meeting &m1, meeting &m2) {
		if (m1.getStart_hour() == m2.getStart_hour())
		///daca ora de inceput este egala, comparam folosind ora de sfarsit
		{
			return maimic(m1.getFinish_hour(), m2.getFinish_hour());
		}
		else
		//altfel comparam orele de inceput
		{
			return maimic(m1.getStart_hour(), m2.getStart_hour());
		}
	});
}
