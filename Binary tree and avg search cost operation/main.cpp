#include "BTree.h"
#include <iostream>
#include <fstream>
#include <iomanip>

template<typename T>
BTree<T> read_file(string file_name);

using namespace std;

int main()
{
	float f;
	string filename;
	filename = "2l";
	BTree<int> new_tree = read_file<int>("data-files/" + filename);
	
    cout << new_tree << endl;

    f = new_tree.get_average_search_time();
    cout<< "\nAverage search cost is\t" << setprecision(7) << f << endl;

    cout << endl;
}

template<typename T>
BTree<T> read_file(string file_name)
{
    ifstream is(file_name);
    
    BTree<T> new_tree;
    is >> new_tree;
    return new_tree;
}
