/* 
Implements a simple templated stack using the templated LinkedList from class

DO NOT EDIT THE CLASS DECLARATION BELOW. You will not submit this file.
*/

#ifndef __STACK_H
#define __STACK_H

#include "template-linkedlist.hpp"
#include <iostream>
#include <iostream>

using namespace std;

template <class T>
class Stack
{
private:
  LinkedList<T>* stack;
public:
  Stack();  // Constructor -- should allocate the stack 

  T& peek();  // Returns a reference to the topmost value without removing it

  void push(T val);  //Add the value to the top of the stack
  T pop();  //Removes and returns the value on top of the stack. If stack is empty, throw StackEmpty
  
  bool empty(); //Checks if the stack is empty

  Stack(const Stack<T>&);  //Copy constructor

  const Stack<T>& operator=(const Stack<T>& copy);  // Copy assignment

  ~Stack();  // Destructor -- deallocate the stack
};


//Prints the stack -- you can use this to test your stack, but you
// won't use this when implementing CallStack 
template <class T>
ostream& operator<<(ostream& out, Stack<T>& s)
{
  Stack<T> temp = s;

  while(!temp.empty())
  {
    out << temp.pop() << endl;
  }
  return out;
}

//An exception thrown when peek/pop is called with an empty stack
struct StackEmpty : public exception {
   const char * what () const throw () {
      return "The stack is empty!";
   }
};

/* 
DO NOT EDIT ABOVE THIS LINE
*/

//HINT: None of the following functions should be more than a few lines long. Let the
//  LinkedList do all the work 

/*Function call: Stack()
Description: Constructor for class Stack
Driver: Anthony Sarim
Navigator: Ricardo Frumento*/
template <class T>
Stack<T>::Stack()
{
  /* TO DO! */
  stack = new LinkedList<T>; //Creates new object of type LinkedList<T>
}

/*Function call: stack.peek()
Description: Checks if the stack is empty, if not returns the value stored at the tail node
Driver: Anthony Sarim
Navigator: Ricardo Frumento*/
template <class T>
T& Stack<T>::peek()
{
  /* TO DO! */
  if(stack->empty()){ //Exception handling
    throw StackEmpty();
  }
  else {
    Node<T>* temp; //Creates new pointer of type Node<T>
    temp =  stack->getTail(); //Assigns Tail pointer to new pointer
    return temp->value(); //returns new pointer data of type T
  }
}

/*Function call: stack.push(x)
Description: Inserts a node with value x after the tail node
Driver: Anthony Sarim
Navigator: Ricardo Frumento*/
template <class T>
void Stack<T>::push(T val)
{
  /* TO DO! */
  stack->insert(val, stack->getSize()); //Calls insert with the new node of type T
}

/*Function call: stack.pop()
Description: Stores the tail node value on a variable and removes the tail node. Returns the stored value
Driver: Anthony Sarim
Navigator: Ricardo Frumento*/
template <class T>
T Stack<T>::pop()
{
  /* TO DO! */
  T rem; //Creates new pointer of type Node<T>
  rem = stack->getTail()->value(); //Assigns Tail pointer to new pointer
  stack->remove(stack->getSize()-1); //Call remove with new pointer as the argument
  return rem;
}

/*Function call: stack.empty()
Description: Checks if the stack is empty by checking if the linked list is empty. Returns true or false
Driver: Ricardo Frumento
Navigator: Anthony Sarim*/
template <class T>
bool Stack<T>::empty()
{
  /* TO DO! */
  bool x; //Creates a boolean variable
  x = stack->empty(); //Calls empty on the this->stack
  return x; //Returns the boolean variable
}

/*Function call: Stack(copyStack)
Description: Creates a new linked list and stores the copyStack linked list on it
Driver: Ricardo Frumento
Navigator: Anthony Sarim*/
template <class T>
Stack<T>::Stack(const Stack<T>& copy)
{
  /* TO DO! */
  stack = new LinkedList<T>; //creates a new LinkedList of type T
  stack = copy.stack; //copies the LinkedList into the new Stack
}

/*Function call: newStack = oldStack
Description: copys the linked list in the RHS stack to the LHS stack linked list. Returns a pointer to the new stack
Driver: Ricardo Frumento
Navigator: Anthony Sarim*/
template <class T>
const Stack<T>& Stack<T>::operator=(const Stack<T>& copy)
{
  /* TO DO! */
  stack = copy.stack; //Copies the stack of the RHS to the LHS
  return *this; //Returns the updated/copied Stack
}

/*Function call: delete stack
Description: Calls the linked list destructor to delete the stack
Driver: Ricardo Frumento
Navigator: Anthony Sarim*/
template <class T>
Stack<T>::~Stack()
{
  /* TO DO! */
  delete this->stack; //Calls the destructor to delete the stack of linked list of type T
}

#endif 
