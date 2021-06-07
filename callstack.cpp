#include "callstack.h"

ostream& operator<<(ostream& out, Function_t& s)
{
  out << "Function " << s.name << " with " << s.numArguments << " args and ";
  out << s.numLocals << " locals" ;
  return out;
}

/*Function call: callStack.call(function, RA, BP, *args, *locals)
Description: Pushes to the info stack the function information and to the rawStack the data to be stored
Driver: Ricardo Frumento
Navigator: Anthony Sarim*/
void CallStack::call(Function_t f, int RA, int BP, int *args, int *locals){
  /* TO DO! */
  info.push(f); //Adds element f of type Function_t to info
  for(int i = 0; i < f.numArguments; i++){ //Loops through the elements of args
    rawStack.push(args[f.numArguments - i - 1]); //Populates rawStack with Arguments in descending order
  }
  rawStack.push(RA); //Pushes RA immediately following the Arguments
  rawStack.push(BP); //Adds BP after the RA, prior to the Locals.
  for(int j = 0; j < f.numLocals; j++){ //Loops through the elements of locals
    rawStack.push(locals[j]); //Populates rawStack with locals in ascending order
  }
}

/*Function call: callStack.currentFunction()
Description: Returns a Function_t struct with the current function being executed information
Driver: Ricardo Frumento
Navigator:Anthony Sarim*/
Function_t CallStack::currentFunction(void)
{
  /* TO DO! */
  Function_t ret; //Creates one object of type Function_t
  ret = info.peek(); //Checks the top of the info stack for the element
  return ret; //Returns Function_t, the desired function.
}

/*Function call: callStack.getLocal(pos)
Description: Checks if the desired position is valid, if not throws an exception. To find the desired data
             runs a loop popping all the previous data from rawStack and pushing onto a temporary stack
             until the next data is the requested. Stores the requested data. Pops the temporary data and
             pushes onto the rawStack. Returns the requested data
Driver: Ricardo Frumento
Navigator: Anthony Sarim*/
int CallStack::getLocal(int n){
  /* TO DO! */
  Stack<int> tempStack; //Creates temporary stack of ints
  int localN; //Declares an int variable
  Function_t tempF = currentFunction(); //Initializes an object of type Function_t with the current function being run
  if(n > tempF.numLocals){ //Exception handling
    throw InvalidIndex();
  }
  for(int i = 0; i < n; i++){ //Loops through the necessary elements to reach the local at position n.
    tempStack.push(rawStack.pop()); // Populates tempStack by popping off from rawStack and pushing onto tempStack.
  }
  localN = rawStack.peek(); //Checks the current value at the top of the rawStack
  while(!tempStack.empty()){ //Lopps through the necessary elements to complete rawStack
    rawStack.push(tempStack.pop()); //Empties the temporary stack and repopulates rawStack
  }
  return localN; //Returns the int stored in the desired position to the stack
}

/*Function call: callStack.setLocal(pos, x)
Description: Checks if the desired position is valid, if not throws an exception. To find the desired position
             runs a loop popping all the previous data from rawStack and pushing onto a temporary stack
             until the next position is the requested. Pops the data in the requested position and pops the given
             value. Pops the temporary data and pushes onto the rawStack.
Driver: Ricardo Frumento
Navigator: Anthony Sarim*/
void CallStack::setLocal(int n, int val)
{
  /* TO DO! */
  Stack<int> tempStack; //Creates temporary stack of ints
  Function_t tempF = currentFunction(); //Initializes an object of type Function_t with the current function being run
  if(n >= tempF.numLocals){ //Exception handling
    throw InvalidIndex();
  }
  for(int i = 0; i < n + 1; i++){ //Loops through the necessary elements to reach the local at position n.
    tempStack.push(rawStack.pop()); //Populates tempStack by popping off from rawStack and pushing onto tempStack.
  }
  if (!tempStack.empty()) { tempStack.pop(); } //Checks if the temporary Stack is empty, if not pops the first element
  rawStack.push(val); //Pushes the new value, int val, onto the stack
  while(!tempStack.empty()){ //Lopps through the necessary elements to complete rawStack
    rawStack.push(tempStack.pop()); //Empties the temporary stack and repopulates rawStack.
  }
}

/*Function call: callStack.getArg(pos)
Description: Checks if the desired position is valid, if not throws an exception. To find the desired data
             runs a loop popping all the previous data from rawStack and pushing onto a temporary stack
             until the next data is the requested. Stores the requested data. Pops the temporary data and
             pushes onto the rawStack. Returns the requested data.
Driver: Anthony Sarim
Navigator: Ricardo Frumento*/
int CallStack::getArg(int n)
{
  /* TO DO! */
  Stack<int> tempStack; //Creates an temporary stack of type int
  int argN; //Declares an int variable
  Function_t tempF = currentFunction(); //Initializes an object of type Function_t with the current function being run
  if(n > tempF.numArguments){ //Exception handling
    throw InvalidIndex();
  }
  for(int i = 0; i < tempF.numLocals + 2 + n; i++){ //Loops through the necessary elements to reach the desired one
    tempStack.push(rawStack.pop()); //Pops of from rawStack the elements, while beings added to the temporary stack of ints
  }
  argN = rawStack.peek(); //Checks the current value at the top of the rawStack
  while(!tempStack.empty()){ //Lopps throuhg the necessary elements to complete rawStack
    rawStack.push(tempStack.pop()); //Empities the temporary stack and repopulates de rawStack
  }
  return argN; //Returns the int stored in the desired position in the stack
}

/*Function call: callStack.setArg(pos, x)
Description: Checks if the desired position is valid, if not throws an exception. To find the desired position
             runs a loop popping all the previous data from rawStack and pushing onto a temporary stack
             until the next position is the requested. Pops the data in the requested position and pops the given
             value. Pops the temporary data and pushes onto the rawStack.
Driver: Anthony Sarim 
Navigator: Ricardo Frumento*/
void CallStack::setArg(int n, int val)
{
  /* TO DO! */
  Stack<int> tempStack; //Creates an temporary stack of type int
  Function_t tempF = currentFunction(); //Initializes an object of type Function_t with the current function being run
  if(n >= tempF.numArguments){ //Exception handling
    throw InvalidIndex();
  }
  for(int i = 0; i < tempF.numLocals + 3 + n; i++){ //Loops through the necessary elements to reach the desired one
    tempStack.push(rawStack.pop()); //Pops of from rawStack the elements, while beings added to the temporary stack of ints
  }
  if (!tempStack.empty()) { tempStack.pop(); } //Checks if the temporary stack is empty, if not, pops the first element
  rawStack.push(val); //Pushes the new value onto the stack
  while(!tempStack.empty()){ //Lopps throuhg the necessary elements to complete rawStack
    rawStack.push(tempStack.pop()); //Empities the temporary stack and repopulates de rawStack
  }
}

/*Function call: callStack.getBP()
Description: To find the desired data runs a loop popping all the previous data from rawStack and pushing onto
             a temporary stack until the next data is the requested. Stores the requested data. Pops the
             temporary data and pushes onto the rawStack. Returns the requested data.
Driver: Anthony Sarim 
Navigator: Ricardo Frumento*/
int CallStack::getBP()
{
  /* TO DO! */
  Stack<int> tempStack; //Creates an temporary stack of type int
  int BP; //Declares an int variable
  int test;
  Function_t tempF = info.peek(); //Initializes an object of type Function_t with the current function being run 
  for(int i = 0; i < tempF.numLocals; i++){ //Loops through the necessary elements to reach the desired one
    tempStack.push(rawStack.pop()); //Pops of from rawStack the elements, while beings added to the temporary stack of ints
  }
  BP = rawStack.peek(); //Checks the current value at the top of the rawStack
  while(!tempStack.empty()){ //Lopps throuhg the necessary elements to complete rawStack
    rawStack.push(tempStack.pop()); //Empities the temporary stack and repopulates de rawStack
  }
  return BP; //Returns the int stored in the desired position in the stack
}

/*Function call: callStack.getRA()
Description: To find the desired data runs a loop popping all the previous data from rawStack and pushing onto
             a temporary stack until the next data is the requested. Stores the requested data. Pops the
             temporary data and pushes onto the rawStack. Returns the requested data.
Driver: Anthony Sarim 
Navigator: Ricardo Frumento*/
int CallStack::getRA()
{
  /* TO DO! */
  Stack<int> tempStack; //Creates an temporary stack of type int
  int RA; //Declares an int variable
  Function_t tempF = currentFunction(); //Initializes an object of type Function_t with the current function being run 
  for(int i = 0; i < tempF.numLocals + 1; i++){ //Loops through the necessary elements to reach the desired one
    tempStack.push(rawStack.pop()); //Pops of from rawStack the elements, while beings added to the temporary stack of ints
  }
  RA = rawStack.peek(); //Checks the current value at the top of the rawStack
  while(!tempStack.empty()){ //Lopps throuhg the necessary elements to complete rawStack
    rawStack.push(tempStack.pop()); //Empities the temporary stack and repopulates de rawStack
  }
  return RA; //Returns the int stored in the desired position in the stack
}

/*Function call: callStack.do_return()
Description: Using the functions information runs a loop popping all elements from rawStack. After this, pops
             the information from the info stack.
Driver: Anthony Sarim 
Navigator: Ricardo Frumento*/
void CallStack::do_return(void)
{
  /* TO DO! */
  Function_t tempF = currentFunction(); //Initializes an object of type Function_t with the current function being run
  for (int i = 0; i < tempF.numArguments + tempF.numLocals + 2; i++){ //Loops through all the elements of one function
      rawStack.pop(); //Removes all the elements
  }
  info.pop(); //Removes the function info
}

/*Function call: cout << callStack;
Description: Operator overload the prints the formated data of the function being executed
Driver: Anthony Sarim 
Navigator: Ricardo Frumento*/
ostream& operator<<(ostream& out, CallStack& s)
{
  /* TO DO! */
  Function_t tempF = s.currentFunction(); //Creates an objects of type Function_t and assigns the current function running
  for (int i = 0; i < tempF.numLocals; i++){ //Loops through all elements in local array
    cout << s.getLocal(i) << " Local " << i << " for " << tempF.name << endl; //Output
  }
  cout << s.getBP() << " BP for " << tempF.name << endl; //Output
  cout << s.getRA() << " RA for " << tempF.name << endl; //Output
  for (int i = 0; i < tempF.numArguments; i++){ //Loops through all elements in arg array
    cout << s.getArg(i) << " Arg " << i << " for " << tempF.name << endl; //Output
  }

  return out;
}