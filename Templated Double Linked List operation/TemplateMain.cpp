#include "TemplateDoublyLinkedList.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

int main () {
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DoublyLinkedList<string> dll;
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    stringstream ss;
    ss << i;
    dll.insertLast(ss.str());
  }
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at front with value 10,20,30,..,100
  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    stringstream ss;
    ss << i;
    dll.insertFirst(ss.str());
  }
  cout << "list: " << dll << endl << endl;
  
  // Copy to a new list
  cout << "Copy to a new list" << endl;
  DoublyLinkedList<string> dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  // Assign to another new list
  cout << "Assign to another new list" << endl;
  DoublyLinkedList<string> dll3;
  dll3=dll;
  cout << "list3: " << dll3 << endl << endl;
  
  // Delete the last 10 nodes
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeLast();
  }
  cout << "list: " << dll << endl << endl;
  
  // Delete the first 10 nodes
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeFirst();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;

  // more testing...
  // add tests for insertAfter, insertBefore
cout<< endl;
  cout<<"To test for inserting or removing given a position:" << endl;
  // add tests for insertAfter, insertBefore
  // add tests for DoublyLinkedListLength

  for (int i=10;i<=100;i+=10) {
    stringstream ss1;
    ss1 << i;
    dll.insertLast(ss1.str());
  }
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;


  //insertafter
  cout << "Insert after node with value 50" << endl;
  stringstream ss2;
    ss2 << 50;
  DListNode<string> *newnode1 = new DListNode<string>(ss2.str());
  dll.insertAfter(*newnode1, "55");
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;


  //insertbefore
  cout << "Insert before node with value 50" << endl;
  stringstream ss3;
    ss3 << 50;
  DListNode<string> *newnode2 = new DListNode<string>(ss3.str());
  dll.insertBefore(*newnode2, "45");
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;




  // add tests for removeAfter, removeBefore


  //removeafter
  cout << "Remove after node with value 40" << endl;
  stringstream ss4;
    ss4 << 40;
  DListNode<string> *newnode3 = new DListNode<string>(ss4.str());
  dll.removeAfter(*newnode3);
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;


  //removebefore
  cout << "Remove before node with value 60" << endl;
  stringstream ss5;
    ss5 << 60;
  DListNode<string> *newnode4 = new DListNode<string>(ss5.str());
  dll.removeBefore(*newnode4);
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;

  
  return 0;
}
