/*
 * File:   LinkedList.cpp
 * Author: Ovidiu Andrei Radulescu
 *
 * Last modified 29/03/2017
 * Implements the LinkedList class.
 */

#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include "linked_list.h"
using namespace std;

//creates an empty list
LinkedList::LinkedList()
{


}

//creates a list with an initial value to store
LinkedList::LinkedList(int value)
{
  //creates a new node at the head
  head = new Node;
  //inserts the inputted value into the head
  head->data = value;
  //sets the tail the same asthe head, since there's only one element
  tail = head;

}

//copy constructor (performs a deep copy)
LinkedList::LinkedList(const LinkedList& rhs)
{
  //initiates the new list
  head = nullptr;
  tail = head;
  //gets the first node of the inputted list
  Node *temp = rhs.head;
  int value;
  //loops through the inputted list
  while(temp != nullptr)
  {
    value = temp->data;
    //appends the values of the inputted list to our new list
    this->append(value);
    temp = temp->next;
  }

}


//destroys (cleans up) the list
LinkedList::~LinkedList()
{
  //gets the first node of the list
  Node *ref = head;
  Node *temp = new Node;
  //loops through the list
  while(ref != nullptr)
  {
    //deletes the node while keeping track of what's the next one
    temp = ref;
    ref = ref->next;
    delete temp;
    temp = nullptr;
  }
}

//adds a value to the head of the list
void LinkedList::push(int value)
{
  //we make a new node with the inputted value
  Node *ref = new Node;
  ref->data = value;
  //we set our new node to point to the (old) head
  ref->next = head;
  //we set our new node as the new head
  head = ref;

}

//gets the last element from the list, without removing it
//requires: list not empty
int LinkedList::peekTail()
{
  int value;
  //tests if the list isn't empty
  assert(head !=nullptr);
  //fetches the tail's value and returns it
  value = tail->data;
    return value;
}

//prints the list in order from head to tail
string LinkedList::toString() const
{
  string allValues;
  //we get the first node of the list
  Node *ref = head;
  //loops through the list
  while(ref != nullptr)
  {
    //adds the numbers to a string
    allValues.append(to_string(ref->data));
    //moves to the next node
    ref = ref->next;
    //if the next node isn't empty, add a space to the string
    if(ref != nullptr)
      allValues.append(" ");

  }
    return allValues;
}

//removes and returns the value at the head of the list
//requires: list not empty
int LinkedList::pop()
{
  int value;
  //tests if the list is empty
  assert(head != nullptr);
  //fetches the head's value
  value = head->data;
  //stores the head's pointer
  Node *temp = head;
  //assigns the new head
  head= head->next;
  //deletes old head
  delete temp;
  return value;
}

//adds a value to the end of the list
void LinkedList::append(int value)
{
  //creates our new node that needs to be added
  Node* ref = new Node;
  ref->data = value;
  ref->next = nullptr;
  //if the list is empty we actually need to 'push' the value
  if(head == nullptr)
    {
      head = ref;
      tail = head;
    }
    else
    {
      //sets our new node as the last node in the list
      tail->next = ref;
      //tail is assigned to the new node
      tail = ref;
    }


}

//appends the deep copies of the nodes of rhs on to the end of this list
void LinkedList::appendList(const LinkedList& rhs)
{
  //gets the first node of the rhs list
  Node *ref = rhs.head;
  int value;
  //loops through the rhs list
  while(ref != nullptr)
  {
    //gets the value of the current node
    value = ref->data;
    //appends the value to this list
    this->append(value);
    //moves to the next node
    ref = ref->next;
  }
}

//inserts a value immediately after the first occurrence of afterValue,
//if afterValue is not in the list then inserts at the tail
void LinkedList::insertAfter(int value, int afterValue)
{
  //a flag for testing if the value has been inserted
  bool notFound = true;
  //gets the first node of the list
  Node *ref = head;
  //our new node that needs to be inserted
  Node *extra = new Node;
  extra->data = value;
  extra->next = nullptr;
  //loops through the list until the end
  //or until the value has been inserted
  while(notFound && ref!=nullptr)
  {
    //tests if our current node's value is the one requested
    if(ref->data == afterValue)
    {
      //inserts our new node between the current node and the next
      extra->next = ref->next;
      ref->next = extra;
      //changes the flag value
      notFound = false;
    }
    ref = ref->next;
  }
  //if the afterValue isn't in the list
  //we append our new node to the end
  if(notFound)
  {
    tail->next = extra;
    tail = extra;
  }
}

//removes all occurrences of value from the list
void LinkedList::removeAllOccurences(int value)
{
  //gets the first node
  Node *ref = head;
  //tests if the list is empty
  //and if the head is an occurrence of the value
  if(ref != nullptr)
    if(ref->data == value)
    {
      //deletes the node if the condition was met
      head = ref->next;
      delete ref;
      ref = head;
    }
    //loops through the list
  while(ref != nullptr)
  {
    //gets the next node for testing
    Node *temp = ref->next;
    //checks if node is empty
    if(temp != nullptr)
    //checks if the node is an occurrence
      if (temp->data == value)
        {
          //if so, removes it
          ref->next = temp->next;
          delete temp;
        }
    ref = ref->next;
  }
}

//reverses the list
void LinkedList::reverse()
{
//this just points the tail at the first node, doesn't affect the actual reversing
  tail = head;
  //creates two nodes
  Node *ref = nullptr;
  Node *next = nullptr;
  //reverses the nodes from beginning
  while(head != nullptr)
  {
    //switches the nodes' next positions and assigns new heads
    next = head->next;
    head->next = ref;
    ref = head;
    head = next;
  }
  //sets the last reversed node as the head
  head = ref;
}

//checks if two lists are equal in state (contain the same values in the same order)
bool LinkedList::operator ==(const LinkedList& other) const
{
  bool verify;
  //puts both lists into a string
  string lhs = this->toString();
  string rhs = other.toString();
  //compares the two strings and returns true if equal
  verify = !(lhs.compare(rhs));
    return verify;
}

//checks if two lists are not equal in state
bool LinkedList::operator !=(const LinkedList& other) const
{
  bool verify;
  //puts both lists into a string
  string lhs = this->toString();
  string rhs = other.toString();
  //compares the strings and returns true if not equal
  verify = lhs.compare(rhs);
    return verify;
}

//pushes a new value onto the head of the list
LinkedList& LinkedList::operator +(int value)
{
  //uses the push method
  this->push(value);
    return *this;
}

//copy assignment operator (performs a deep copy)
LinkedList& LinkedList::operator =(const LinkedList& rhs)
{
  //flags for checking if either list ended before the other
  bool lhsFlag = false, rhsFlag = false;
  //gets the heads of both lists
  Node *lhsNode = head;
  Node *rhsNode = rhs.head;
  Node *temp= new Node;
  //loops until one of the lists ends
  while(true)
  {
    //copies the data from right list to left list
    lhsNode->data = rhsNode->data;
    //checks if the next node is a nullptr
    //breaks the loop if so
    if(lhsNode->next == nullptr)
    {
      lhsFlag = true;
      break;
    }
    else
    {
    //moves to the next node, but keeps track of the previous
      temp = lhsNode;
      lhsNode=lhsNode->next;
    }
    //same method as the left list
    if(rhsNode->next == nullptr)
    {
      rhsFlag = true;
      break;
    }
    else
    //we don't need to keep track of previous nodes for rhs
      rhsNode = rhsNode->next;
  }
  //checks which list ended first(so it's shorter than the other)
  //if the left list ended first, we need to append the remaining
  //values of the right list
    if(lhsFlag)
    {
      rhsNode = rhsNode->next;
      while (rhsNode !=nullptr) {
        append(rhsNode->data);
        rhsNode = rhsNode->next;
      }
    }
    //if the right list ended first, we need to delete the extra
    //nodes of the left list
    if(rhsFlag)
    {
      //sets the tail as the last modified node
      tail = temp;
      tail->next = nullptr;
      //delets the rest of the nodes
      while(lhsNode != nullptr)
      {
        temp = lhsNode;
        lhsNode = lhsNode->next;
        delete temp;
        temp = nullptr;
      }
    }

    return *this;
}

//pushes values from an input stream onto the front of the list
std::istream& operator>>(std::istream &in, LinkedList &value)
{
  int number;
  //loops through the input stream
  while(in)
  {
    //checks if the current character is an endline
    if(in.peek() == '\n')
      break;
    //gets a number from the input stream and appends it
    in>>number;
    value.push(number);

  }
    return in;
}

//writes the values, in order, to an output stream
std::ostream& operator<<(std::ostream &out, const LinkedList &value)
{
  //uses the toString method for outputting
  out<<value.toString();
    return out;
}
