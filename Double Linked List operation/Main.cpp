#include "DoublyLinkedList.h"
#include <iostream>
using namespace std;
int main () {
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DoublyLinkedList dll;
  cout << "list: " << dll << endl << endl;
  
  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertLast(i);
  }
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;

  // Insert 10 nodes at front with value 10,20,30,..,100
  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    dll.insertFirst(i);
  }
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;
  
  // Copy to a new list
  cout << "Copy to a new list" << endl;
  DoublyLinkedList dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  // Assign to another new list
  cout << "Assign to another new list" << endl;
  DoublyLinkedList dll3;
  dll3=dll;
  cout << "list3: " << dll3 << endl << endl;
  
  // Delete the last 10 nodes
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeLast();
  }
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;
  
  // Delete the first 10 nodes
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeFirst();
  }
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;

  // more testing...

  cout<< endl;
  cout<<"To test for inserting or removing given a position:" << endl;
  // add tests for insertAfter, insertBefore
  // add tests for DoublyLinkedListLength

  for (int i=10;i<=100;i+=10) {
    dll.insertLast(i);
  }
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;


  //insertafter
  cout << "Insert after node with value 50" << endl;
  DListNode *newnode1 = new DListNode(50);
  dll.insertAfter(*newnode1, 55);
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;


  //insertbefore
  cout << "Insert before node with value 50" << endl;
  DListNode *newnode2 = new DListNode(50);
  dll.insertBefore(*newnode2, 45);
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;




  // add tests for removeAfter, removeBefore


  //removeafter
  cout << "Remove after node with value 40" << endl;
  DListNode *newnode3 = new DListNode(40);
  dll.removeAfter(*newnode3);
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;


  //removebefore
  cout << "Remove before node with value 60" << endl;
  DListNode *newnode4 = new DListNode(60);
  dll.removeBefore(*newnode4);
  cout << "list: " << dll << endl;
  cout << "Length of dll:\t" << DoublyLinkedListLength(dll) << endl << endl;



  
  return 0;
}
