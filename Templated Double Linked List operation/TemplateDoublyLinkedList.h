#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;
template <class T>
class DoublyLinkedList; // class declaration

// list node
template <class T>
struct DListNode {
  T obj;
  DListNode<T> *prev, *next;
  DListNode(T e = T(), DListNode<T> *p = NULL, DListNode<T> *n = NULL)
    : obj(e), prev(p), next(n) {}
};

// doubly linked list
template <class T>
class DoublyLinkedList {
private:
  DListNode<T> header, trailer;
public:
  DoublyLinkedList() : header(T()), trailer(T()) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  DoublyLinkedList(const DoublyLinkedList<T>& dll); // copy constructor
  ~DoublyLinkedList(); // destructor
  DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& dll); // assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  void insertAfter(DListNode<T> &p, T newobj);
  void insertBefore(DListNode<T> &p, T newobj);
  T removeAfter(DListNode<T> &p);
  T removeBefore(DListNode<T> &p);
};

// output operator
template <typename T> ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);
// return the list length
template <typename T> int DoublyLinkedListLength(DoublyLinkedList<T>& dll);











// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
  // Initialize the list
  header.next = &trailer; trailer.prev = &header;

  // Copy from dll
  for ( const DListNode<T>* i = dll.getFirst(); (i != dll.getAfterLast()); i=i->next )
  {
    insertLast(i->obj);
  }

}

// assignment operator
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{
  // Delete the whole list
  DListNode<T> *prev_node, *node = header.next;
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
template <typename T>
void DoublyLinkedList<T>::insertFirst(T newobj)
{ 
    DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;
}

// insert the new object as the last one
template <typename T>
void DoublyLinkedList<T>::insertLast(T newobj)
{
  DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev,&trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

// remove the first object from the list
template <typename T>
T DoublyLinkedList<T>::removeFirst()
{ 
  if (isEmpty())
  throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = header.next;
  node->next->prev = &header;
  header.next = node->next;
  T obj = node->obj;
  delete node;
  return obj;
}

// remove the last object from the list
template <typename T>
T DoublyLinkedList<T>::removeLast()
{
  if (isEmpty())
  throw EmptyDLinkedListException("Empty Doubly Linked List");
  DListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev = node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}

// destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
  DListNode<T> *prev_node, *node = header.next;
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
template <typename T>
T DoublyLinkedList<T>::first() const
{ 
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return header.next->obj;
}

// return the last object
template <typename T>
T DoublyLinkedList<T>::last() const
{
  if (isEmpty())
    throw EmptyDLinkedListException("Empty Doubly Linked List");
  return trailer.prev->obj;
}

// insert the new object after the node p
template <typename T>
void DoublyLinkedList<T>::insertAfter(DListNode<T> &p, T newobj)
{
    /* Complete this function */
    
    DListNode<T> *newNode = new DListNode<T>(newobj);
    
    DListNode<T> *current = 0;
    DListNode<T> *node = header.next;

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
template <typename T>
void DoublyLinkedList<T>::insertBefore(DListNode<T> &p, T newobj)
{
    /* Complete this function */

    DListNode<T> *newNode = new DListNode<T>(newobj);
    
    DListNode<T> *current = 0;
    DListNode<T> *node = header.next;

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
template <typename T>
T DoublyLinkedList<T>::removeAfter(DListNode<T> &p)
{
    /* Complete this function */
    DListNode<T> *current = 0;
    DListNode<T> *node = header.next;

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
    T obj = node->next->obj;
    delete current;
    return obj;
}

// remove the node before the node p
template <typename T>
T DoublyLinkedList<T>::removeBefore(DListNode<T> &p)
{
    /* Complete this function */
    DListNode<T> *current = 0;
    DListNode<T> *node = header.next;

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
    T obj = node->next->obj;
    delete current;
    return obj;
}

// return the list length
template <typename T>
int DoublyLinkedListLength(DoublyLinkedList<T>& dll)
{
  DListNode<T> *current = dll.getFirst();
  int count = 0;
  while(current != dll.getAfterLast()) 
  {
    count++;
    current = current->next; //iterate
  }
  return count;
}

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll)
{
  DListNode<T> *current = dll.getFirst();
  while(current != dll.getAfterLast()) 
  {
    out << current->obj << ' ';
    current = current->next; //iterate
  }
  return out;
}
