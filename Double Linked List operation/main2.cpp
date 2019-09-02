#include "part2.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int main () {
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  MinQueue mq;
  
  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl << endl;
  for (int i=10;i<=100;i+=10) 
  {
    mq.enqueue(i);
  }
  mq.display();
  cout << "The current length of the queue list:\t" << mq.size() << endl;
  

cout << "The minimum in the list:\t" << mq.min() << endl << endl;


  // Delete the first 10 nodes
  cout << "Delete the first 5 nodes" << endl;
  for (int i=0;i<5;i++)
  {
    mq.dequeue();
  }
  mq.display();
  cout << "The current length of the queue list:\t" << mq.size() << endl;

  
cout << "The minimum in the list:\t" << mq.min() << endl << endl;

  
  cout << "Enter a random number in the queue, say 45" << endl;
  mq.enqueue(45);
  mq.display();
  cout << "The current length of the queue list:\t" << mq.size() << endl;
  

cout << "The minimum in the list:\t" << mq.min() << endl << endl;
 
  return 0;
}
