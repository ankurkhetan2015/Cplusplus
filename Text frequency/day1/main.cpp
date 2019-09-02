#include "my_map.h"
#include "text_freq.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void save_stop_words(vector<key_value<string, double>> words)
{
    ofstream fs("stop_words.txt");
    //for(key_value<std::string, double> word : words)
    for(int i = 0; i < 200; i++)
    {
        fs << words[i].key << endl;
    }
}

vector<string> read_stop_words()
{
    vector<string> stop_words;
    fstream fs("stop_words.txt");
    string word;
    while(fs >> word)
    {
        stop_words.push_back(word);
    }
    return stop_words;
}

/*
    How to run
        - copy and pase this main.cpp into your project directory
        - replace you current main file with this one
        - in the same folder you got this file you should see
            - (book).txt
                - this is the file that you will be reading for text frequencies
            - stop_words.txt
                - this is a file containing the stop words that will be used on the text file
        - now you should be able to compile
        - when you want to run the file
            - type ./main <file name>
            - the file name will be the name of the book that you moved into the directory earlier
*/
int main(int argc, char *argv[])
{   
    if(argc < 2)
    {
        cout << "error: not enough args: Usage: ./main <file_name>" << endl;
        return -1;
    }
    
    string file_name = argv[1]; 

    string file = read_file(file_name);
    auto map = create_freq_map(file);
    auto vec = vectorize_map(map);
    vector<string> stop_words = read_stop_words();
    remove_stop_words(vec,stop_words);
    print_top_20_freqs(vec,cout);
}
