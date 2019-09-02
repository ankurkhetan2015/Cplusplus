#include <cstdlib>
#include <iostream>
#include <stdexcept>
using namespace std;
#include "DoublyLinkedList.h"



class MinQueue 
{

private: 
DoublyLinkedList ll; // internal DoublyLinkedList object
int length;

public: 
MinQueue() : ll() // constructor
{length = 0; } 
~MinQueue() 
{ 
ll.~DoublyLinkedList(); 
} // destructor 
bool isEmpty( ) const 
{ 
return ll.isEmpty(); 
}  
void enqueue(int x) 
{ 
ll.insertLast(x);
length++;
}
int dequeue( ); 
int min() const;
int size() const;

void display();
};



int MinQueue::dequeue()
{ 
	if (isEmpty()) 
		throw EmptyDLinkedListException("Access to an empty queue"); 
	length--;
	return ll.removeFirst(); 

}

int MinQueue::min() const
{
	if (isEmpty()) 
		throw EmptyDLinkedListException("Access to an empty queue");

    DListNode *node = ll.getFirst();
    int currentmin = node->obj;

	while(node != ll.getAfterLast()) 
	{
		if(currentmin > node->obj)
		{
			currentmin = node->obj;
		}
		node = node->next; //iterate

	}

	return currentmin;
}

int MinQueue::size() const
{
	return length;
}

void MinQueue::display()
{
	cout << "The list:";

	DListNode *current = ll.getFirst();
	while(current != ll.getAfterLast()) 
	{
		cout << current->obj << ' ';
		current = current->next; //iterate
	}

	cout << endl;
}