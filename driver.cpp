#include "callstack.h"
#include <stdio.h>

/*
This is a short program to test your callstack. Note that this does not cover all of the capabilities
of the callstack, and the TAs will test other examples. The correct output can be found in output.txt

Feel free to modify this file for additional testing.  You will not submit this file.
*/

int main()
{
    CallStack test;
    char name1[] = "myFunction1";
    char name2[] = "myFunction2";
    char name3[] = "myTestFunction";
    Function_t myFunction1 = {name1, 2, 1};  //Using the functions from the printing example
    Function_t myFunction2 = {name2, 1, 2};
    Function_t myFunction3 = { name3, 10, 5 };

    int myFunc1Args[] = { 50, 42};
    int myFunc1Locals[] = {32};
    int myFunc2Args[] = {30};
    int myFunc2Locals[] = {200, 10};
    int myFunc3Args[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int myFunc3Locals[] = { 10, 20, 30, 40, 50 };

    test.call(myFunction1, 2000, 300, myFunc1Args, myFunc1Locals);
    cout << test;  //Print stack for myFunction1
    //cout << "========================" << endl;
    //cout << "32 Local 0 for myFunction1" << endl <<
    //    "300 BP for myFunction1" << endl <<
    //    "2000 RA for myFunction1" << endl <<
    //    "50 Arg 0 for myFunction1" << endl <<
    //    "42 Arg 1 for myFunction1" << endl;
    test.call(myFunction2, 1000, 2, myFunc2Args, myFunc2Locals);


    cout << "------------------------" << endl;
    cout << test;  //Print stack for myFunction2
    test.call(myFunction3, 5000, 100, myFunc3Args, myFunc3Locals);
    cout << "------------------------" << endl;
    cout << test;
    //cout << "========================" << endl;
    //cout << "10 Local 1 for myFunction2" << endl <<
    //    "200 Local 0 for myFunction2" << endl <<
    //    "2 BP for myFunction2" << endl <<
    //    "1000 RA for myFunction2" << endl <<
    //    "30 Arg 0 for myFunction2" << endl;
    test.do_return();
    cout << "------------------------" << endl;
    cout << test;  //Print stack for myFunction1 again
    //cout << "========================" << endl;
    //cout << "32 Local 0 for myFunction1" << endl <<
    //    "300 BP for myFunction1" << endl <<
    //    "2000 RA for myFunction1" << endl <<
    //    "50 Arg 0 for myFunction1" << endl <<
    //    "42 Arg 1 for myFunction1" << endl;

    cout << "------------------------" << endl;
    try {
        test.setArg(1, 1111);
    }
    catch (InvalidIndex e) {
        cout << e.what() << endl;
    }
    try{
        test.setArg(2, 1111);
    }
    catch (InvalidIndex e)
    {
        cout << e.what() << endl;  //Should catch an exception
    }

    try {
        test.setLocal(0, 2222);
    }
    catch (InvalidIndex e){
        cout << e.what() << endl;
    }
    try{
        test.setLocal(1, 2222);
    }
    catch (InvalidIndex e)
    {
        cout << e.what() << endl;  //Should catch an exception
    }

    //Check that changes were made
    cout << "------------------------" << endl;
    cout << test;  //Print stack for myFunction1 again
    //cout << "========================" << endl;
    //cout << "2222 Local 0 for myFunction1" << endl <<
    //    "300 BP for myFunction1" << endl <<
    //    "2000 RA for myFunction1" << endl <<
    //    "50 Arg 0 for myFunction1" << endl <<
    //    "1111 Arg 1 for myFunction1" << endl;

    return 0;
}