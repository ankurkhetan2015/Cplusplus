#include <iostream>
#include <string>
#include "my_map.h"
#include "text_freq.h"

using namespace std;

int main()
{
    /*my_map<string, int> m;
    m["c"] = 10;
    m["f"] = 3;
    m["b"] = 4;
    m["a"] = 5;
    m["d"] = 15;
    m["e"] = 15;
    m["f"] = 15;
    
    cout << endl << m << endl;
    
    auto curr = m.begin();
    
    while(curr != m.end())
    {
        cout << *curr << endl;
        curr++;
    }*/
	
	// Load the words
	string words = read_file("TFOTRnew.txt");

	// Count the frequencies
	my_map<string, double> wordFrequenciesMap = create_freq_map(words);

	// Get the counted results
	vector<key_value<string, double>> wordFrequenciesVector = vectorize_map(wordFrequenciesMap);

	// Exclude stop words
	vector<string> stopWords;
	stopWords.push_back("a");
	stopWords.push_back("the");
	stopWords.push_back("that");
	stopWords.push_back("of");
	stopWords.push_back("for");
	stopWords.push_back("in");
	stopWords.push_back("to");
	stopWords.push_back("have");
	stopWords.push_back("was");
	stopWords.push_back("were");
	stopWords.push_back("it");
	stopWords.push_back("It");
	stopWords.push_back("is");
	stopWords.push_back("as");
	stopWords.push_back("The");
	stopWords.push_back("have");
	stopWords.push_back("I");
	stopWords.push_back("but");
	stopWords.push_back("be");
	stopWords.push_back("at");
	stopWords.push_back("by");
	stopWords.push_back("had");
	stopWords.push_back("its");
	stopWords.push_back("or");
	stopWords.push_back("not");
	stopWords.push_back("has");
	stopWords.push_back("from");
	stopWords.push_back("and");

	remove_stop_words(wordFrequenciesVector, stopWords);

	// Print the top 20 words
	print_top_20_freqs(wordFrequenciesVector, cout);

	return 0;
}