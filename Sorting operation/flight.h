#pragma once
#include <string>

struct Flight 
{
  std::string flightNum;     //2 letters, 3 digits
  std::string destination;   //multi-word city name
  std::string departureTime; //HH:MM, 24-hr format
  std::string gateNum;       //1 letter, 1 digit

  Flight();
  Flight(std::string fn, std::string dest, std::string dt, std::string gn);
  ~Flight();
  //...
};

//compare this Flight object against another Flight object
//returns true if this object is >= other
bool compareToDestination(Flight f1, Flight f2);
bool compareToDepartureTime(Flight f1, Flight f2);

using namespace std;
// Definitions of user defined type exceptions 
struct invalid_input : public exception 
{
	virtual const char* what() const throw()
	{ return "Invalid Flight input"; }
};

struct missing_file : public exception 
{
	virtual const char* what() const throw()
	{ return "Attempted to read from an unknown file."; }
};