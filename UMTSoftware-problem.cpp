// UMTSoftware-problem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include<iostream>
#include<fstream>

#include<vector>
#include"meeting.h"
#include"calendar.h"
#include<string>
#include "Tests.h"


using namespace std;

//-----------------------------------------------------------------
//Descriere: functia citeste datele din fisier si returneaza rezultatele prin intermediul parametrilor
//
//input:c1,c2-adrese de calendare,meeting_time_minutes-int
//folosim & pentru ca rezultatele sa ramana salvate la iesirea din functie
//output:c1,c2-adrese de calendare,meeting_time_minutes-int
//-----------------------------------------------------------------
void load_Data_From_File(calendar &c1, calendar &c2, int &meeting_time_minutes)
{
	fstream f;
	f.open("C:\\Users\\Ionela\\source\\repos\\UMTSoftware-problem\\UMTSoftware-problem\\datein.txt", ios::in);
	//-------Citire date din primul calendar------------------
	string range_min, range_max;
	f >> range_min >> range_max;

	string start_hour, finish_hour;
	vector<meeting> v1;
	v1.reserve(50);

	while (f >> start_hour >> finish_hour)
	{	if(start_hour=="Stop") 
		///daca start_hour=="Stop" inseamna ca s-au terminat de citit datele din primul calendar,
		//intrerupem citirea folosind break;
		{ 
			break;
		}
		else
		{
			meeting m = meeting(start_hour, finish_hour);//cream un obiect de tip meeting
			v1.push_back(m);//il adaugam in vectorul nostru de mitinguri
		}
	}
	//setam datele ce tocmai le-am citit pentru calendar1
	c1.setRange_min(range_min);
	c1.setRange_max(range_max);
	c1.setBooked(v1);

	//---------Citire date din al 2-lea calendar----------------
	f >>range_min>>range_max;
	vector<meeting> v2;
	v2.reserve(50);

	while (f >> start_hour >> finish_hour)
	{
		if (start_hour == "Stop")
		///daca start_hour=="Stop" inseamna ca s-au terminat de citit datele din al doilea calendar,
		//intrerupem citirea folosind break;
		{
			break;
		}
		else
		{
			meeting m = meeting(start_hour, finish_hour);//cream un obiect de tip meeting
			v2.push_back(m);//il adaugam in vectorul nostru de mitinguri
		}
		
	}
	//setam datele ce tocmai le-am citit pentru calendar2
	c2.setRange_min(range_min);
	c2.setRange_max(range_max);
	c2.setBooked(v2);
	
	//citim numarul de minute de care e nevoie pentru a stabili un meeting intre cele 2 persoane
	f >> meeting_time_minutes;
	f.close();
}
//-----------------------------------------------------------------
//Descriere: functia determina stringul cel mai mare ca ora
//-----------------------------------------------------------------
string maxim(string s1, string s2)
{
	string ora1 = "", ora2 = "", min1 = "", min2 = "";
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
	if (ora1 > ora2)
	{
		return s1;
	}
	else
	{
		if (ora1 == ora2)
		{
			if (min1 > min2)
			{
				return s1;
			}
			else
			{
				return s2;
			}
		}
		else
		{
			return s2;
		}
	}
}
//-----------------------------------------------------------------
//Descriere: functia determina stringul cel mai mare ca ora
//-----------------------------------------------------------------
string minim(string s1, string s2)
{
	string ora1 = "", ora2 = "", min1 = "", min2 = "";
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
		return s1;
	}
	else
	{
		if (ora1 == ora2)
		{
			if (min1 < min2)
			{
				return s1;
			}
			else
			{
				return s2;
			}
		}
		else
		{
			return s2;
		}
	}
}
//-----------------------------------------------------------------
//Descriere: functia face un singur calendar din 2 calendare, adaugand fiecare meeting pe rand
//-----------------------------------------------------------------
calendar create_one_calendar(calendar c1,calendar c2)
{
	calendar c3 = calendar();

	c3.setRange_min(maxim(c1.getRange_min(), c2.getRange_min()));
	///c3.setRange_min() seteaza ora de la care sunt disponibili amandoi

	c3.setRange_max(minim(c1.getRange_max(), c2.getRange_max()));
	///c3.setRange_max() seteaza ora la care cel putin unul pleaca acasa, deci nu se mai pot vedea


	vector<meeting> v1;
	vector<meeting> v2;
	//adaugam meetingurile din primul calendar
	for (int i = 0; i < c1.getSizeBooked(); i++)
	{
		v1.push_back(c1.getAllBooked()[i]);
	}
	//adaugam meetingurile din al doilea calendar
	for (int i = 0; i < c2.getSizeBooked(); i++)
	{
		v2.push_back(c2.getAllBooked()[i]);
	}

	//setam valorile pentru c3
	//setBooked face pus_back deci nu se pierd valorile din v1 cand se pun cele dn v2
	c3.setBooked(v1);
	c3.setBooked(v2);

	return c3;
}
//-----------------------------------------------------------------
//Descriere: functia determina daca stringul s1 e mai mic decat stringul s2, din punct de vedere al orei
//in caz afirmativ returneaza true, altfel false
//-----------------------------------------------------------------
bool maiMic(string s1, string s2)
{
	string ora1 = "", ora2 = "", min1 = "", min2 = "";
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
//Descriere: functia determina daca timpul dintre 2 meetinguri este >= cu timpul ce este necesar pentru ca cele 2 persoane
//se intalneasca
//returneaza true in caz afirmativ si false altfel
//-----------------------------------------------------------------
bool enoughtTime(int meeting_time_minutes, string s1, string s2)
{
	//s2 =ora de inceput al meetingului de pe pozitia i+1
	//s1 = ora de sfarsit al meetingului de pe pozitia i

	string ora1 = "", ora2 = "", min1 = "", min2 = "";
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

	//convertim stringurile in inturi pentru a putea face calcule cu ele
	int Ora1 = stoi(ora1);
	int Ora2 = stoi(ora2);
	int Min1 = stoi(min1);
	int Min2 = stoi(min2);

	//TotalMin-numarul total de minute dintre cele 2 meetinguri
	int TotalMin = (Ora2 * 60 + Min2) - (Ora1 * 60 + Min1);

	return (meeting_time_minutes <= TotalMin);
}
//-----------------------------------------------------------------
//Descriere: functia afiseaza pe ecran toate intervalele libere dintre 2 meetinguri care sunt mai mari
//decat meeting_time_minutes
//-----------------------------------------------------------------
void determina_interbal_liber(int meeting_time_minutes, calendar &c3)
{
	for (int i = 0; i < c3.getSizeBooked()-1; i++)
	{
		if (maiMic(c3.getAllBooked()[i].getStart_hour(),c3.getRange_min()))
			//c3.getAllBooked()[i].getStart_hour() < c3.getRange_min()
			//daca meetingul curent incepe mai repede decat ora la care sunt disponibile ambele persoane se trece la
			//urmatorul meeting
		{
			continue;
		}
		else
		{
			if (maiMic(c3.getAllBooked()[i].getFinish_hour(), c3.getRange_max())==false)
				///(c3.getAllBooked()[i].getFinish_hour() > c3.getRange_max()
				//daca meetingul curent se termina dupa ora la care mai sunt disponibile ambele persoane returnam nimic pentru 
				//a iesi din functie
			{
				return ;
			}
			else
			{
				if (maiMic(c3.getAllBooked()[i].getFinish_hour(),c3.getAllBooked()[i + 1].getStart_hour()))
				{
					//c3.getAllBooked()[i].getFinish_hour() < c3.getAllBooked()[i + 1].getStart_hour()
					//daca ora la acre se temina meetingul i e mai mica decat ora la care incepe urmatorul meeting calculam daca 
					//avem suficient timp pentru o noua intalnire

					//fac calcule sa vad daca timpul liber este >=meeting_time_minutes
					if (enoughtTime(meeting_time_minutes, c3.getAllBooked()[i].getFinish_hour(), c3.getAllBooked()[i + 1].getStart_hour()) == true)
					{
						//in caz afirmativ afisam intervalul cerut
						cout << c3.getAllBooked()[i].getFinish_hour() << " " << c3.getAllBooked()[i + 1].getStart_hour() << endl;
					}
				}
			}
		}
	}

	//verificam daca dupa ultimul meeting din calendar mai exista timp liber pana cand una dintre persoane nu mai e disponibila
	if (enoughtTime(meeting_time_minutes, c3.getAllBooked()[c3.getSizeBooked() - 1].getFinish_hour(), c3.getRange_max()))
	{
		cout << c3.getAllBooked()[c3.getSizeBooked() - 1].getFinish_hour() << " " << c3.getRange_max() << endl;

	}
}

int main()
{

	//--------------Principiu--------------------------------------------------
	//1)Citim cele 2 calendare si numarul de minute necesar pentru ca cele 2 persoane sa se intalneasca
	//2)Punem toate meetingurile intr-un singur calendar si deteminam intervalul orar in care ambele persoane sunt '
	//disponibile
	//3)sortam meetingurile crescator dupa ora de inceput si ora de sfarsit
	//4) Determinam toate intervalele in care cele 2 se pot vedea:
	//		-un interval este valid daca ora la care se termina meetingul i e < decat ora la cre se termina meetingul i+1(urmator)
	//		-un interval e suficient de mare daca nr de minute sunt >= numarul de minute cerute pentru meeting
	//-------------------------------------------------------------------------

	//---------------Important--------------------------------------------------
	//1)datele de intrare sunt citite din fisier si rezultatele sunt afisate pe ecran
	//2)la citirea din fisier datele sunt formatate ca in exemplul de mai jos:
	//Exemplu+explicatii: 
	//09:00 20:00				<----pe prima linie sunt limitele primului calendar
	//09:00 10:30				<----incepand cu linia a 2-a se citesc meetingurile din calendarul1, pana la intalnirea
	//12:00 13:00					Stop Calendar
	//16:00 18:00				<----format meetinguri: Start_hour Stop_hour, acestea vor fi despartite obligatoriu prin spatiu
	//Stop Calendar				<----Dupa intalnirea Stop Calendar se citesc datele pentru Calendarul2,dupa acelasi principiu
	//10:00 18:30				<----limitele calendarului 2
	//10:00 11:30				<----se citesc meetingurile din calendarul1, pana la intalnirea Stop Calendar
	//12:30 14:30				<----specificarea unei orese face in formatul "00:00"-"23:59"
	//14:30 15:00
	//16:00 17:00
	//Stop Calendar				<----Dupa intalnirea celui de-al 2-lea Stop Calendar se termina de citit datele din calendarul 2
	//30						<----Citim numarul minutelor necesare pentru un nou meeting(se va memora in meeting_time_minutes)
	//
	//3)Consideram datele de intrare ca fiind valide, adica meetingurile nu depasesc intervalul de munca dat,
	//orele sunt mentionate in formatul cerut, meetingurile sunt date in ordine si nu se suprapun unele cu altele 
	//pentru acelasi calendar. 
	//Datele dintre obligatoriu delimitate de Stop Calendar. 
	//------------------------------------------------------------------------

	//cream cele 2 calendare pe care le vom citi din fisier si initializam meeting_time_minutes = 0;
	calendar c1 =calendar();
	calendar c2 =calendar();
	int meeting_time_minutes = 0;

	//citim datele din fisier
	load_Data_From_File(c1,c2,meeting_time_minutes);
	
	//executam teste pentru datele citite din fisier
	//daca testele sunt executate cu succes se va afisa  "all tests from Test_Load_Data_From_File run ok"
	cout << "Rezultatele testelor sunt:" << endl;
	Test_Load_Data_From_File(c1, c2, meeting_time_minutes);

	//cream calendarul 3 , cel in care vom pune toate meetingurile la un loc
	calendar c3 = create_one_calendar(c1,c2);
	//sortam noul calendar crescator atat dupa ora de inceput cat si dupa ora de sfarsit
	c3.sort_calendar();

	//cout-urile de mai jos au fost folosite pentru a verifica ce exista in c3, calendarul comun celor doi, dupa sortare
	//-----------------------------------------------------------------------------------------------------
	//cout << c3.getRange_min() << " " << c3.getRange_max() << endl<<endl;
	/*cout << "main" << endl;
	for (int i = 0; i < c3.getSizeBooked(); i++)
	{
		cout << c3.getAllBooked()[i].getStart_hour() << " " << c3.getAllBooked()[i].getFinish_hour() << endl;
	}*/

	//determinam toate intervalele libere in care cele 2 persoane se pot vedea
	cout <<endl<< "Intervalel orare in care cele 2 persoane se pot intalni sunt:" << endl;
	determina_interbal_liber(meeting_time_minutes, c3);
	cout << endl << "Sper ca ti-am fost de ajutor!	O zi frumoasa. :-)" <<endl;

	//--------------Posibile imbuatatiri--------------------------------------------------
	//1)Teste pentru toate functiile
	//2)Impartirea aplicatiiei si functiilor in:
	//-Domanin:care va caontine clasele si functionalitatile de baza
	//-Repo/RepoFile(nu neapart necesar in cazul nostru, dar daca erau mai mult de 2 calendare era nevoie)
	//-Controller
	//-UI
	//------------------------------------------------------------------------------------

	return 0;
}
