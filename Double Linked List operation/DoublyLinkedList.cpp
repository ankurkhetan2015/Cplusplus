#include "DoublyLinkedList.h"
#include <stdexcept>



// copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& dll)
{
  // Initialize the list
	header = 0;
	header.next = &trailer; trailer.prev = &header;

	// Copy from dll
	for ( const DListNode* i = dll.getFirst(); i!= dll.getAfterLast(); i=i->next )
	{
		insertLast(i->obj);
	}

}

// assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& dll)
{
  // Delete the whole list
	DListNode *prev_node, *node = header.next;
	while (node != &trailer) 
	{
		prev_node = node;
		node = node->next;
		delete prev_node;
	}
	header.next = &trailer;
	trailer.prev = &header;
  /* Complete this function */
	//copy from dll
	new(this) DoublyLinkedList(dll);

	return *this;
}

// insert the new object as the first one
void DoublyLinkedList::insertFirst(int newobj)
{ 
    DListNode *newNode = new DListNode(newobj, &header, header.next);
	header.next->prev = newNode;
	header.next = newNode;
}

// insert the new object as the last one
void DoublyLinkedList::insertLast(int newobj)
{
	DListNode *newNode = new DListNode(newobj, trailer.prev,&trailer);
	trailer.prev->next = newNode;
	trailer.prev = newNode;
}

// remove the first object from the list
int DoublyLinkedList::removeFirst()
{ 
	if (isEmpty())
	throw EmptyDLinkedListException("Empty Doubly Linked List");
	DListNode *node = header.next;
	node->next->prev = &header;
	header.next = node->next;
	int obj = node->obj;
	delete node;
	return obj;
}

// remove the last object from the list
int DoublyLinkedList::removeLast()
{
	if (isEmpty())
	throw EmptyDLinkedListException("Empty Doubly Linked List");
	DListNode *node = trailer.prev;
	node->prev->next = &trailer;
	trailer.prev = node->prev;
	int obj = node->obj;
	delete node;
	return obj;
}

// destructor
DoublyLinkedList::~DoublyLinkedList()
{
	DListNode *prev_node, *node = header.next;
	while (node != &trailer) 
	{
		prev_node = node;
		node = node->next;
		delete prev_node;
	}
	header.next = &trailer;
	trailer.prev = &header;
}

// return the first object
int DoublyLinkedList::first() const
{ 
	if (isEmpty())
		throw EmptyDLinkedListException("Empty Doubly Linked List");
	return header.next->obj;
}

// return the last object
int DoublyLinkedList::last() const
{
	if (isEmpty())
		throw EmptyDLinkedListException("Empty Doubly Linked List");
	return trailer.prev->obj;
}

// insert the new object after the node p
void DoublyLinkedList::insertAfter(DListNode &p, int newobj)
{
    /* Complete this function */
    
    DListNode *newNode = new DListNode(newobj);
    
    DListNode *current = 0;
    DListNode *node = header.next;

	while(node != &trailer) 
	{
		if(node->obj == p.obj)
		{
			current = node;
			break;
		}
		node = node->next; //iterate

	}
    
    newNode->next = current->next;
	newNode->prev = current;
	newNode->next->prev=newNode;
	current->next=newNode;
}

// insert the new object before the node p
void DoublyLinkedList::insertBefore(DListNode &p, int newobj)
{
    /* Complete this function */

    DListNode *newNode = new DListNode(newobj);
    
    DListNode *current = 0;
    DListNode *node = header.next;

	while(node != &trailer) 
	{
		if(node->obj == p.obj)
		{
			current = node;
			break;
		}
		node = node->next; //iterate

	}
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev=newNode;
}

// remove the node after the node p
int DoublyLinkedList::removeAfter(DListNode &p)
{
    /* Complete this function */
    DListNode *current = 0;
    DListNode *node = header.next;

	while(node != &trailer) 
	{
		if(node->obj == p.obj)
		{
			current = node->next;
			break;
		}
		node = node->next; //iterate

	}
    
    node->next = current->next;
    current->next->prev = node;
    int obj = node->next->obj;
    delete current;
    return obj;
}

// remove the node before the node p
int DoublyLinkedList::removeBefore(DListNode &p)
{
    /* Complete this function */
    DListNode *current = 0;
    DListNode *node = header.next;

	while(node != &trailer) 
	{
		if(node->obj == p.obj)
		{
			current = node->prev;
			break;
		}
		node = node->next; //iterate

	}
    node->prev = current->prev;
    current->prev->next = node;
    int obj = node->next->obj;
    delete current;
    return obj;
}

// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll)
{
	DListNode *current = dll.getFirst();
	int count = 0;
	while(current != dll.getAfterLast()) 
	{
		count++;
		current = current->next; //iterate
	}
	return count;
}

// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll)
{
	DListNode *current = dll.getFirst();
	while(current != dll.getAfterLast()) 
	{
		out << current->obj << ' ';
		current = current->next; //iterate
	}
	return out;
}