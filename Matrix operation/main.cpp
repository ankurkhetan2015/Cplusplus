// main.cpp
// Tests all functionality of the class My_matrix class.

#include <iostream>
#include <fstream>
#include "My_matrix.h"

int main(){

  // Some test cases are expected to throw an exception.
  // Add more try and catch blocks as necessary for your code
  // to finish execution.

  try{

    // Test 1
    // * Create an object of type My_matrix, called m1, using constructor
    // * Initialize m1 in main (by assigning numbers to matrix elements)
    // * Display m1 on the screen using the operator <<
    My_matrix m1(2, 3);
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(0, 2) = 3;
    m1(1, 0) = 4;
    m1(1, 1) = 5;
    m1(1, 2) = 6;
    cout << "[m1]\n" << m1 << endl;

    // Test 2
    // * Create an object of type My_matrix, called m2, using (default)
    //   constructor
    // * Open an input file containing a matrix (row by row)
    // * Initialize m2 by reading from the input file using
    //   the operator >>
    // * Open an output file (can be empty)
    // * Write m2 to the output file using the operator <<
    My_matrix m2;
    ifstream input("m2.txt");
    input >> m2;
    ofstream output("m2_output.txt");
    output << m2;
    input.close();
    output.close();
    cout << "[m2]\n" << m2 << endl;

    // Test 3
    // * Use the copy constructor to make a copy of m1 called m3
    // * Apply the copy assignment to m1 called m4
    // * Display m3 and m4 on the screen using the operator <<
    My_matrix m3(m1);
    My_matrix m4;
    // copy assignment is optional
    m4=m1;
    cout << "[m3]\n" << m3 << endl;
    cout << "[m4]\n" << m4 << endl;

    // Test 4
    // * Test the matrix multiplication operator (operator*)
    // * Apply the multiplication operator to valid and invalid cases
    // * Display the resulting matrix and its number of rows and columns

    // create a matrix to operate with
    My_matrix m5(3, 3);
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        m5(i, j) = i + j;
    cout << "[m5]\n" << m5 << endl;

    cout << "[m1 * m5]\n" << m1 * m5 << endl;
    try {
      cout << "[m5 * m1]\n" << m5 * m1 << endl;
    } catch(exception &error){
      cerr << "Error: " << error.what() << endl << endl;
    }

    // Test 5
    // * Test the matrix addition operator (operator+)
    // * Apply the multiplication operator to valid and invalid cases
    // * Display the resulting matrix and its number of rows and columns
    cout << "[m1 + m3]\n" << m1 + m3 << endl;
    try {
      cout << "[m1 + m5]\n" << m1 + m5 << endl;
    } catch(exception &error){
      cerr << "Error: " << error.what() << endl << endl;
    }


  } catch(exception &error){
    cerr << "Error: " << error.what() << endl;
  }
}
