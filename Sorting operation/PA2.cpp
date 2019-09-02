#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "sort.h"

std::vector<Flight> readFlights(std::string inputFile);
void writeFlights(std::string outputFile, std::vector<Flight>); //write to file
void printFlights(std::vector<Flight>); //print to terminal


int main()
{
	/*
    first read flights in files using readFlights()
    descen10.csv	ascen10.csv     rand10.csv
    descen100.csv	ascen100.csv	rand100.csv
    descen1000.csv	ascen1000.csv	rand1000.csv
    descen10000.csv ascen10000.csv	rand10000.csv
	*/

	/*
    then use each of the sorting functions on each of the generated vectors
	*/

	/*
    then output each of the resultant sorted vectors
    format them so that they look like the table of the front of the
    instructions

    Flight Number	Destination Departure   Time	        Gate Number
    AA223			LAS VEGAS	21:15			A3
    BA023			DALLAS		21:00			A3
    AA220			LONDON		20:30			B4
    VI303			MEXICO		19:00			A7
    BA087			LONDON		17:45			A7
    AA342			PARIS		16:00			A7
    VI309			PRAGUE		13:20			F2
    QU607			TORONTO		08:30			F2
    AA224			SYDNEY		08:20			A7
    AF342			WASHINGTON	07:45			A3
	*/

	bool doMain = true;
	while (doMain)
	{
		std::string input;
		string filename;

		std::cout << "Choose File (1 - 13), 'q' to quit, 'f' to input a file: " << std::endl;
		std::cout << "1. descen10.csv" << '\t' << '\t' << "2. ascen10.csv" << '\t' << '\t' << "3. rand10.csv" << std::endl;
		std::cout << "4. descen100.csv" << '\t' << "5. ascen100.csv" << '\t' << '\t' << "6. rand100.csv" << std::endl;
		std::cout << "7. descen1000.csv" << '\t' << "8. ascen1000.csv" << '\t' << "9. rand1000.csv" << std::endl;
		std::cout << "10. descen10000.csv" << '\t' << "11. ascen10000.csv" << '\t' << "12. rand10000.csv" << std::endl;
		std::cout << "13. rand100000.csv" << std::endl;
		
		std::string flightFiles[ ] = {"descen10.csv",	"ascen10.csv", "rand10.csv",
		"descen100.csv", "ascen100.csv", "rand100.csv", "descen1000.csv", "ascen1000.csv",
		"rand1000.csv", "descen10000.csv", "ascen10000.csv", "rand10000.csv", "rand100000.csv"};

		std::vector<Flight> flightSort;

		while (true)
		{
			std::cin >> input;

			int num_input = stoi(input);	
			
			if (num_input > 0 && num_input < 14)
			{
				filename = flightFiles[num_input - 1];
				flightSort = readFlights("input/" + filename); //read the chosen list file
				break;
			}
			else if (input == "q")
			{
				doMain = false; //prepare to end program
				break;
			}
			else if (input == "f")
			{
				std::cout << "File name: ";
				std::cin >> filename;
				flightSort = readFlights(filename); //read the typed-in file
				break;
			}
			else
			{
				std::cout << "Choose a File (1 - 13): " << std::endl; //repeat
			}
		}

		if (!doMain) break; //exit program if the 'q' command is used


		//////////////////////////////////////////////////////
		//Begin sorting and printing to terminal
		//////////////////////////////////////////////////////
		printFlights(flightSort);

		//Selection sort
		std::cout << std::endl << "Selection Sort (Destination): " << std::endl;
		std::vector<Flight> destFlightSelectSort = selection_sort(flightSort, ByDestination);
		writeFlights("dest_select_"+filename,destFlightSelectSort);
		if (flightSort.size() <= 10) printFlights(destFlightSelectSort); //only print if input < 10 objects

		std::cout << std::endl << "Selection Sort (Departure Time): " << std::endl;
		std::vector<Flight> departFlightSelectSort = selection_sort(flightSort, ByDepartureTime);
		writeFlights("depart_select_"+filename,departFlightSelectSort);
		if (flightSort.size() <= 10) printFlights(departFlightSelectSort);

		//Insertion sort
		std::cout << std::endl << "Insertion Sort (Destination): " << std::endl;
		std::vector<Flight> destFlightInsSort = insertion_sort(flightSort, ByDestination);
		writeFlights("dest_ins_"+filename,destFlightInsSort);
		if (flightSort.size() <= 10) printFlights(destFlightInsSort);

		std::cout << std::endl << "Insertion Sort (Departure Time): " << std::endl;
		std::vector<Flight> departFlightInsSort = insertion_sort(flightSort, ByDepartureTime);
		writeFlights("depart_ins_"+filename,departFlightInsSort);
		if (flightSort.size() <= 10) printFlights(departFlightInsSort);

		//Bubble sort
		std::cout << std::endl << "Bubble Sort (Destination): " << std::endl;
		std::vector<Flight> destFlightBubSort = bubble_sort(flightSort, ByDestination);
		writeFlights("dest_bub_"+filename,destFlightBubSort);
		if (flightSort.size() <= 10) printFlights(destFlightBubSort);

		std::cout << std::endl << "Bubble Sort (Departure Time): " << std::endl;
		std::vector<Flight> departFlightBubSort = bubble_sort(flightSort, ByDepartureTime);
		writeFlights("depart_bub_"+filename,departFlightBubSort);
		if (flightSort.size() <= 10) printFlights(departFlightBubSort);
		
		std::cout << endl <<  "Sorting complete." << endl << endl;
		
		/*
		then fill out the rest of the questions on the instructions 
		- the number of comparisons
	
		- to test your functions experimentally use difftime explained here 
		http://www.cplusplus.com/reference/ctime/time/
		*/
	
	}

	return 0;
}

//read in the flights from the input file at fileName and store them in a vector
std::vector<Flight> readFlights(std::string inputFile)
{
	std::vector<Flight> flights;
	std::string in_line;
	
	std::ifstream is(inputFile);
	if (!is) throw missing_file();
	
	//verify the header
	getline(is, in_line);
	if (in_line != "FLIGHT NUMBER,DESTINATION,DEPARTURE TIME,GATE NUMBER") invalid_input();
	
	//start reading
	std::string flightNum_get;
	std::string destination_get;
	std::string departureTime_get;
	std::string gateNum_get;
	while(!is.eof()) //go line by line in the file
	{		
		getline(is, flightNum_get, ',');     //flighNum, 2 letters, 3 digits
		getline(is, destination_get, ',');   //destination, multi-word city name
		getline(is, departureTime_get, ','); //departureTime, HH:MM, 24-hr format
		if(departureTime_get[0] == ' ')  //check to see if there is a comma in the destination and handle it:
		{
			destination_get += departureTime_get; //add the incorrect departure time onto the destination,
			getline(is, departureTime_get, ',');   //re-get the departure time
			getline(is, gateNum_get);            //gateNum, 1 letter, 1 digit
		}
		else
		{
			getline(is, gateNum_get);            //gateNum, 1 letter, 1 digit
		}
		
		//This terminates on a final empty line without throwing an exception:
		if (is.eof() && flightNum_get.size() == 0 && destination_get.size() == 0 && departureTime_get.size() == 0 && gateNum_get.size() == 0) break;

		//automatically throw exception on empty data fields:
		if (flightNum_get.size() == 0 || destination_get.size() == 0 || departureTime_get.size() == 0 || gateNum_get.size() == 0)
		{
			throw invalid_input();
		}
		
		//Add the current flight to the flights container
		flights.push_back(*(new Flight(flightNum_get, destination_get, departureTime_get, gateNum_get)));
		
		flightNum_get.clear();
		destination_get.clear();
		departureTime_get.clear();
		gateNum_get.clear();

	}
  
	return flights;
}

//write to file
void writeFlights(std::string outputFile, std::vector<Flight> flights)
{
	std::ofstream of(outputFile);
	of << "Flight Number" << ',' << "Destination" << "," << "Departure Time" <<  "," << "Gate Number" << endl;
	for(Flight flight_obj : flights)
	{
		of << flight_obj.flightNum << "," << flight_obj.destination << ",";
		of << flight_obj.departureTime << "," << flight_obj.gateNum << "\n";
	}
}

//print to terminal
void printFlights(std::vector<Flight> flights) 
{
	int disp_w = 20;
	const char separator = ' ';
	
	std::cout << setw(disp_w) << setfill(separator) << "Flight Number" << setw(2*disp_w) << setfill(separator) << "Destination" << 
    setw(disp_w) << setfill(separator) << "Departure Time" << setw(disp_w) << setfill(separator) << "Gate Number" << std::endl;

	for(Flight flight_obj : flights)
	{
		std::cout << setw(disp_w) << setfill(separator) <<flight_obj.flightNum << setw(2*disp_w) << setfill(separator) << flight_obj.destination <<
		setw(disp_w) << setfill(separator) << flight_obj.departureTime << setw(disp_w) << setfill(separator) << flight_obj.gateNum << "\n";
	}
}
