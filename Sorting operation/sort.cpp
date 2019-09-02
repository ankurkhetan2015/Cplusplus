#include "sort.h"

#include <iostream> //deleteme
#include <ctime>


//use this to keep track of comparisons
int num_cmps;


//Selection Sort
std::vector<Flight> selection_sort(std::vector<Flight> flights, SortOption sortOpt)
{
	// sort in ascending/alphabetical order by departure time or destination
	num_cmps = 0;
	clock_t t1, t2; //to calculate computational time
	
	t1 = clock();

	switch (sortOpt)
	{
		case ByDestination:
		{
			for (int i = 0; i < flights.size() - 1; i++) // start from beginning of destination list
			{
				Flight temp = flights[i]; // set first value as a temporary
				int counter = i;
				for (int j = i + 1; j < flights.size(); j++)
				{
					// compare and replace for each smaller value
					if (!compareToDestination(flights[j], temp))
					{
						temp = flights[j];
						counter = j;
					}
				}
				flights[counter] = flights[i];
				flights[i] = temp;
			}
			break;
		}

		case ByDepartureTime:
		{
			for (int i = 0; i < flights.size() - 1; i++) // start from beginning of destination list
			{
				Flight temp = flights[i]; // set first value as a temporary
				int counter = i;
				for (int j = i + 1; j < flights.size(); j++)
				{
					// compare and replace for each smaller value
					if (!compareToDepartureTime(flights[j], temp))
					{
						temp = flights[j];
						counter = j;
					}
				}
				flights[counter] = flights[i];
				flights[i] = temp;
			}
			break;
		}
	}
	
	t2 = clock();
	std::cout << "Experimental Time (in Seconds): " << (double)(t2 - t1)/CLOCKS_PER_SEC << std::endl;
	std::cout << "Number of Comparisons: " << num_cmps << std::endl;
	return flights;
}


//Insertion Sort
std::vector<Flight> insertion_sort(std::vector<Flight> flights, SortOption sortOpt)
{
	//sort in ascending/alphabetical order by either departure time or destination
	num_cmps = 0;
	clock_t t1, t2; //to calculate computational time
	
	t1 = clock();
	
	switch (sortOpt)
	{
		case ByDestination:
		{
			for(int i=1; i < flights.size(); i++)
			{
				Flight temp = flights[i]; //save the next unsorted element
				int j = i; //start from the first unsorted element and sort backwards
				for( ; j > 0 && !compareToDestination(temp, flights[j-1]); j--) 
				{
					flights[j] = flights[j-1]; //step through the previously-sorted region to see if the temp element should go there, and replace
				}
				flights[j] = temp; //insert the current temp element into the sorted region
			}
			break;
		}

		case ByDepartureTime:
		{
			for(int i=1; i < flights.size(); i++)
			{
				Flight temp = flights[i]; //save the next unsorted element
				int j = i; //start from the first unsorted element and sort backwards
				for( ; j > 0 && !compareToDepartureTime(temp, flights[j-1]); j--)
				{
					flights[j] = flights[j-1]; //step through the previously-sorted region to see if the temp element should go there, and replace
				}
				flights[j] = temp; //insert the current temp element into the sorted region
			}
			break;
		}
	}

	t2 = clock();
	std::cout << "Experimental Time (in Seconds): " << (double)(t2 - t1)/CLOCKS_PER_SEC << std::endl;
	std::cout << "Number of Comparisons: " << num_cmps << std::endl;
	return flights;
}


//Bubble Sort
std::vector<Flight> bubble_sort(std::vector<Flight> flights, SortOption sortOpt)
{
	//sort in ascending/alphabetical order by either departure time or destination
	Flight temp; //temporary use to swap elements
	num_cmps = 0;
	clock_t t1, t2; //to calculate computational time
	bool swap; //used to optimize the sort
	
	t1 = clock();

	switch (sortOpt)
	{
		//sorting byDestination
		case ByDestination: 
		{
			for (int i = 0; i < flights.size(); i++)
			{
				swap = true; //initially assume that the file is sorted
				for (int j = 0; j < flights.size() - i - 1; j++)
				{
					//compare elements
						if (!compareToDestination(flights[j+1], flights[j])) //compares the next element with the previous element
						{
							//swap them
							temp = flights[j];
							flights[j] = flights[j + 1];
							flights[j + 1] = temp;
							swap = false; //if swapping took place, file was not sorted
						}
				}

				//if no swapping took place, the file was already sorted and hence stop the sort
				if (swap == true)
				{
					break;
				}
			}
			break;
		}
		//sorting byDepartureTime
		case ByDepartureTime:
		{
			for (int i = 0; i < flights.size(); i++)
			{
				swap = true; //initially assume that the file is sorted
				for (int j = 0; j < flights.size() - i - 1; j++)
				{	//compare elements
					if (!compareToDepartureTime(flights[j+1], flights[j])) //compares the next element with the previous element
					{	
						//swap them
						temp = flights[j];
						flights[j] = flights[j + 1];
						flights[j + 1] = temp;
						swap = false; //if swapping took place, file was not sorted
					}		
				}

				//if no swapping took place, the file was already sorted and hence stop the sort
				if (swap == true)
				{
					break;
				}
			}
			break;
		}
	}

	t2 = clock();
	std::cout << "Experimental Time (in Seconds): " << (double)(t2 - t1)/CLOCKS_PER_SEC << std::endl;
	std::cout << "Number of Comparisons: " << num_cmps << std::endl;
	return flights;
}
