#include "text_freq.h"
#include "my_map.h"
#include "key_value.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>

using namespace std;

string read_file(string file_name)
{
    //this should read the file, and return the string of the whole file
	ifstream inFile;
	inFile.open(file_name.c_str());

	if (!inFile.is_open()) {
		return "";
	}

	string str;
	stringstream ss;

	while (inFile >> str)
	{
		str = remove_punctuation(str);
		ss << str << " ";
	}

	return ss.str();
}

string remove_punctuation(string& text)
{
    string result;
    std::remove_copy_if(text.begin(), text.end(),            
                        std::back_inserter(result), //Store output           
                        std::ptr_fun<int, int>(&std::ispunct));
    return result;
}

my_map<string, double> create_freq_map(const string& text)
{
    my_map<string,double> freq_map;

    //this should find the frequecies of every word in the text
	stringstream ss1(text);
	string word;
	double totalWords = 0;

	while (ss1 >> word)
	{
		freq_map[word]++;
		totalWords++;
	}

	stringstream ss2(text);

	for (my_map<string, double>::map_iter it = freq_map.begin(); it != freq_map.end(); it++)
	{
		word = (*it).key;
		freq_map[word] /= totalWords;
	}

    return freq_map;
}

vector<key_value<string,double>> vectorize_map(my_map<string, double>& freq_map)
{
    vector<key_value<string,double>> freq_vec;

    //this should return a sorted vector of the results
	for (my_map<string, double>::map_iter it = freq_map.begin(); it != freq_map.end(); it++)
	{
		string key = (*it).key;
		double value = (*it).value;
		freq_vec.push_back(key_value<string, double>(key, value));
	}

    return freq_vec;
}

void remove_stop_words(vector<key_value<string,double>>& freq_vec, vector<string> stop_words)
{
	//this function should remove the elements contained in stop_words from freq_vec 
	for (unsigned i = 0; i < stop_words.size(); i++)
	{
		string stop_word = stop_words[i];

		for (int j = (signed) freq_vec.size() - 1; j >= 0; j--)
			if (freq_vec[j].key == stop_word)
				freq_vec.erase(freq_vec.begin() + j);
	}
}

void print_top_20_freqs(const vector<key_value<string,double>>& freq_vec, ostream& out)
{
    //prints the top 20 frequencies to out
	vector<key_value<string, double>> freq_vec_copy;

	for (unsigned i = 0; i < freq_vec.size(); i++)
		freq_vec_copy.push_back(freq_vec[i]);

	for (unsigned i = 0; i < freq_vec_copy.size() - 1; i++)
	{
		for (unsigned j = i + 1; j < freq_vec_copy.size(); j++)
		{
			if (freq_vec_copy[i].value < freq_vec_copy[j].value)
			{
				key_value<string, double> temp = freq_vec_copy[i];
				freq_vec_copy[i] = freq_vec_copy[j];
				freq_vec_copy[j] = temp;
			}
		}
	}


	for (unsigned i = 0; i < freq_vec_copy.size() && i < 20; i++)
		out << freq_vec_copy[i] << endl;
}
