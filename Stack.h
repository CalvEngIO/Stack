/*
* FILENAME:	Stack.h
* AUTHOR:	Orlando S. Hoilett
* EMAIL:	orlandohoilett@gmail.com
* VERSION:	0.0


* AFFILIATIONS
* Calvary Engineering Family Group, USA
*	A group of electronics and science enthusiasts who enjoy builing things


* DESCRIPTION
* This templatizes library provides use of a queue data structure with the
* Arduino environment since namespace std is not natively supported in Arduino.


* UPDATES
* Version 0.0
* 2014/05/02:1357>
*			Submitted code for a CS 201 Introduction to Data Structures class
*			assignment.
* 2015/03/31:2039>
*			Made a few modifications to the code to allow compatability with the
*			Arduino microcontroller	environment and IDE. These modifications
*			include changing "size_t" to "int" and removing the assignment opeartor.
*
*			Added message to indicate to the user when he/she tries to peek when the
*			queue is empty.


* DISCLAIMER
* This code is in the public domain. Please feel free to use, modify, distribute,
* etc. as needed, but please give reference to original author as a courtesy to
* open source developing/-ers.
*
* If you find any bugs in the code, or have any questions, please feel free to
* contact me at orlandohoilett@gmail.com

*/


#ifndef STACK_H
#define STACK_H

template<typename ItemType>

//typedef double ItemType; // stack currently holds doubles
//typedef ItemType ItemType; // stack currently holds doubles


class Stack
{
  private:

	  struct Node
	  {
		  ItemType data;
		  Node *next;
	  };
	  typedef Node* NodePtr;

	  NodePtr myTop;

	  int mySize; //number of items on stack

 
  public:
    // Class Constructor
    // post: stack is created & initialized to be empty
    Stack();

    // Copy Constructor
    // pre: parameter object, rhs, exists
    // post: stack is created to be a copy of the parameter stack
    Stack(const Stack<ItemType>& rhs);

    // Class Deconstructor
    // pre: the stack exists
    // post: the stack is destroyed and any dynamic memory is returned to the system
    ~Stack();

    // Assignment operator
    // Assigns a stack to another
    // pre: both class objects exist
    // post: this class object gets assigned a copy of the parameter class object
	//const Stack<ItemType>& operator= (const Stack<ItemType>& rhs);

    // isEmpty
    // Checks if the stack is empty
    // pre:  A stack exists.
    // post: Returns true if it IS empty, false if NOT empty.
    bool isEmpty() const;

    // push
    // Pushes an item on top of the stack.
    // pre:  Stack exists and item is passed.
    // post: the item is placed on top of the stack, and size is incremented.
    void push(const ItemType& item);

    // pop
    // Pops the top item off the stack.
    // pre:  Stack exists.
    // post: Removes item on top of stack.  If the stack
    //       was already empty, throws a std::underflow_error exception.
    void pop();

    // top
    // Returns the top item of the stack without popping it.
    // pre:  Stack exists.
    // post: Returns item on top of stack.  If the stack
    //       was already empty, throws a std::underflow_error exception.
    ItemType peek() const;

    // size
    // Returns the number of items on the stack.
    // post: Returns size from the private section of class.
    int size() const;

};

// Class Constructor
// post: stack is created & initialized to be empty
template<typename ItemType>
Stack<ItemType>::Stack() :mySize(0), myTop(0)
{
}


// Copy Constructor
// pre: parameter object, rhs, exists
// post: stack is created to be a copy of the parameter stack
template<typename ItemType>
Stack<ItemType>::Stack(const Stack<ItemType>& rhs) :mySize(rhs.mySize), myTop(rhs.myTop)
{
	if (rhs.myTop != 0) {
		//copy first node
		myTop = new Node;
		myTop->data = rhs.myTop->data;

		//copy rest of list
		NodePtr newPtr = myTop;
		for (NodePtr origPtr = rhs.myTop->next; origPtr != 0;
			origPtr = origPtr->next) {
			newPtr->next = new Node;
			newPtr = newPtr->next;
			newPtr->data = origPtr->data;
		}
		newPtr->next = 0; //end of list
	} //end of statement
} //end of copy constructor



// Class Deconstructor
// pre: the stack exists
// post: the stack is destroyed and any dynamic memory is returned to the system
template<typename ItemType>
Stack<ItemType>::~Stack()
{
	while (!isEmpty()) {
		pop();
	}
}


//// Assignment operator
//// Assigns a stack to another
//// pre: both class objects exist
//// post: this class object gets assigned a copy of the parameter class object
//template<typename ItemType>
//const Stack<ItemType>& Stack<ItemType>::operator= (const Stack<ItemType>& rhs)
//{
//	if (this != &rhs) {
//		Stack<ItemType> tmp(rhs);
//		std::swap(mySize, tmp.mySize);
//		std::swap(myTop, tmp.myTop);
//	}
//	return *this;
//}


// isEmpty
// Checks if the stack is empty
// pre:  A stack exists.
// post: Returns true if it IS empty, false if NOT empty.
template<typename ItemType>
bool Stack<ItemType>::isEmpty() const
{
	return mySize == 0;
}


// push
// Pushes an item on top of the stack.
// pre:  Stack exists and item is passed.
// post: the item is placed on top of the stack, and size is incremented.
template<typename ItemType>
void Stack<ItemType>::push(const ItemType& item)
{
	//create new node
	NodePtr p;
	p = new Node;
	p->data = item;
	p->next = 0;

	//if the list is empty, add new node
	if (myTop == 0) {
		myTop = p;
		//mySize++;
	}

	//if not add to top of stack
	else {
		//NodePtr cur;
		//NodePtr prev;
		p->next = myTop;
		myTop = p;
		//mySize++;
	}
	
	mySize++;
}


// pop
// Pops the top item off the stack.
// pre:  Stack exists.
// post: Removes item on top of stack.  If the stack
//       was already empty, throws a std::underflow_error exception.
template<typename ItemType>
void Stack<ItemType>::pop()
{
	//TODO fix this so that it only checks if stack is empty once and not on every call
	//if (mySize == 0) {
	//	throw std::underflow_error("stack is already empty");
	//}
	//else {
		NodePtr tmp = myTop;
		myTop = myTop->next;
		delete tmp;
		mySize--;
	//}
}


// peek
// Returns the top item of the stack without popping it.
// pre:  Stack exists.
// post: Returns item on top of stack.  If the stack
//       was already empty, throws a std::underflow_error exception.
template<typename ItemType>
ItemType Stack<ItemType>::peek() const
{
	////TODO fix this so that it only checks if stack is empty once and not on every call
	//if (mySize == 0) {
	//	throw std::underflow_error("stack is empty");
	//}
	//else {
	if (mySize == 0)
	{
		Serial.println("Stack is empty");
		return NULL;
	}
	else
	{
		return myTop->data;
	}
}


// size
// Returns the number of items on the stack.
// post: Returns size from the private section of class.
template<typename ItemType>
int Stack<ItemType>::size() const
{
	return mySize;
}


//#include "Stack_t.cpp"
#endif
