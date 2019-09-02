#include <iostream>
#include <sstream>
#include <ctype.h>
#include <string.h> //for strcmp()

#include "flight.h"

extern int num_cmps;

Flight::Flight()
{
	//assign some basic strings that still obey expectations:
	flightNum = "AA000";
	destination = "DEFAULT";
	departureTime = "00:00";
	gateNum  = "A0";
}

Flight::Flight(std::string fn, std::string dest, std::string dt, std::string gn)
{
	//checking input format
	//check flight number
	if(fn.size() != 5)
	{cout << endl << " fn:" << fn << " dest:" << dest << " dt:" << dt << " gn:" << gn << ' ' << endl; throw invalid_input();}

	for(int i = 0; i < 2; i++)
	{
		if(!isalpha(fn.at(i))) 
		{cout << endl << " fn:" << fn << " dest:" << dest << " dt:" << dt << " gn:" << gn << ' ' << endl; throw invalid_input();}
	}

	for(int i = 2; i < fn.size(); i++)
	{
		if(!isdigit(fn.at(i))) 
		{cout << endl << " fn:" << fn << " dest:" << dest << " dt:" << dt << " gn:" << gn << ' ' << endl; throw invalid_input();}
	}

	// check destination
	for(int i = 0; i < dest.size(); i++)
	{
		if(isdigit(dest.at(i))) 
		{cout << endl << " fn:" << fn << " dest:" << dest << " dt:" << dt << " gn:" << gn << ' ' << endl; throw invalid_input();}
	}

	//check time format
	stringstream ss;
	char dummy;
	int t1, t2;
	ss << dt;
	ss >> t1 >> dummy >> t2;
	if(t1 < 0 || t1 > 24 || t2 < 0 || t2 > 59)
	{cout << endl << " fn:" << fn << " dest:" << dest << " dt:" << dt << " gn:" << gn << ' ' << endl; throw invalid_input();}

	ss.clear();

	//check gate number, 3 characters including the linebreak
	if(!(gn.size() == 3 || gn.size() == 2)) 
	{cout << endl << " fn:" << fn << " dest:" << dest << " dt:" << dt << " gn:" << gn << ' ' << endl; throw invalid_input();}

	else if(!isalpha(gn.at(0)) && !isdigit(gn.at(1))) 
	{cout << endl << " fn:" << fn << " dest:" << dest << " dt:" << dt << " gn:" << gn << ' ' << endl; throw invalid_input();}


	//Now, assign verified values to the member variables of struct	
	flightNum = fn;			// 2 alphabetic characters followed by a three digit integer
	destination = dest;	    // Name of a city (can be many words) 
	departureTime = dt;		// 24 hour format
	gateNum  = gn;			// 1 alphabetic character followed by a single digit integer
}

Flight::~Flight()
{
}

//return false if f1 < f2; true if f1 >= f2
//i.e. true if f1's destination is alphabetically after f2's
bool compareToDestination(Flight f1, Flight f2)
{
	num_cmps++;

	string dest1 = f1.destination;
	string dest2 = f2.destination;
	
	if (dest1.compare(dest2) >= 0) return true;
	else return false;
}

//return false if f1 < f2; true if f1 >= f2
//i.e. true if f1's time is later than f2's time
bool compareToDepartureTime(Flight f1, Flight f2)
{
	num_cmps++;

	stringstream ss;
	char dummy;
	if(f1.departureTime == f2.departureTime) return true; //equality

	//reach each relevant character as an integer, one by one
	int t1, t2;
	ss << f1.departureTime;
	ss >> t1 >> dummy >> t2;
	int numTime1 = 60*t1 + t2;
	ss.clear();
	
	ss << f2.departureTime;
	ss >> t1 >> dummy >> t2;
	int numTime2 = 60*t1 + t2;
	ss.clear();

	if(numTime1 > numTime2) return true;
	else return false;

}