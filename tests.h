#pragma once
#include<iostream>
#include<cassert>

using namespace std; 

//-----------------------------------------------------------------
//Descriere: functia testeaza daca datele sunt citite corect din fisier
//input: c1,c2 -calendare; meeting_time_minutes-int
//output:true/fallse-bool type
//-----------------------------------------------------------------
bool Test_Load_Data_From_File(calendar c1, calendar c2, int meeting_time_minutes)
{
	assert(c1.getRange_min() == "09:00");
	assert(c1.getRange_max() == "20:00");
	assert(c1.getSizeBooked() == 3);

	assert(c2.getRange_min() == "10:00");
	assert(c2.getRange_max() == "18:30");
	assert(c2.getSizeBooked() == 4);

	assert(meeting_time_minutes == 30);
	cout << "all tests from Test_Load_Data_From_File run ok" << endl;
	return true;
}

//-----------------------------------------------------------------
//In mod normal se fac teste pentru toate functiile sau macar pentru cele mai importante.
//Din lipsa de timp am facut doar functia aceasta, restul rezultatelor le-am urmarit in debugger sau
//cout-uri pe parcurs.

