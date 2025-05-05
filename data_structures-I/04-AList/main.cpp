//*****************************************************************************************************
//
//      This program demonstrates the use of the AList class by instantiating an array-based list of
//      short integers and performing its methods.
//
//      Other files required:
//        1.  aList.h - header file for the AList class
//
//*****************************************************************************************************

#include "aList.h"           // bring in the AList<T> template
#include <iostream>          // for std::cout, std::cerr, std::endl
using namespace std;

//*****************************************************************************************************

// Forward declarations of helper functions:
void displayAList(bool success, AList<short> &shortList);
void checkState(AList<short> &shortList);

//*****************************************************************************************************

int main() {
    // Create an AList of short integers with initial capacity 3
    AList<short> shortList(3);
    short        num;         // value to insert
    int          i = 0;       // index for insertAtIndex
    bool         success;     // result of each operation

    // Report initial state (empty or full)
    checkState(shortList);

    // 1) Insert 10 at the front of the list
    num = 10;
    success = shortList.insertFront(num);
    if (success)
        cout << "insert front: " << num << endl;
    displayAList(success, shortList);

    // 2) Insert 20 at index 0 (shifts existing elements right)
    num = 20;
    success = shortList.insertAtIndex(num, i);
    if (success)
        cout << "insert index " << i << ": " << num << endl;
    displayAList(success, shortList);

    // 3) Insert 30 at the back of the list
    num = 30;
    success = shortList.insertBack(num);
    if (success)
        cout << "insert back: " << num << endl;
    displayAList(success, shortList);

    return 0;  // end program
}

//*****************************************************************************************************

// displayAList: if the last operation succeeded, print the list contents,
// its capacity, current size, and the smallest element.
// Then report if the list is now empty or full.
void displayAList(bool success, AList<short> &shortList) {
    short min;      // will hold the smallest element
    int   cap,      // current capacity of the list
          numVal;  // current number of stored elements

    if (success) {
        shortList.display();           // print each element with its index
        shortList.getSmallest(min);   // find the smallest element
        cap     = shortList.getCapacity();
        numVal  = shortList.getNumValues();

        if (numVal > 0)
            cout << "capacity: " << cap
                 << "\tnumVal: " << numVal
                 << "\tsmallest: " << min << endl;
        else
            cout << "capacity: " << cap
                 << "\tnumValues: " << numVal << endl;

        cout << endl;
    }

    // Always check and report if the list is now empty or full
    checkState(shortList);
}

//*****************************************************************************************************

// checkState: writes to std::cerr (the error stream) if the list is empty or full
void checkState(AList<short> &shortList) {
    if (shortList.isFull())
        cerr << "list is full\n\n";
    else if (shortList.isEmpty())
        cerr << "list is empty\n\n";
}


//*****************************************************************************************************
/*

list is empty

insert front: 10
[0] 10
capacity: 3     numVal: 1       smallest: 10

insert index 0: 20
[0] 20
[1] 10
capacity: 3     numVal: 2       smallest: 10

insert back: 30
[0] 20
[1] 10
[2] 30
capacity: 3     numVal: 3       smallest: 10

list is full

*/


/*

What is cerr?
cerr stands for "character error" and is a standard output stream in C++ used to display error messages or diagnostic information. It is part of the <iostream> library, just like cout and cin.
Key Characteristics of cerr:
Unbuffered:

cerr writes output immediately to the console without waiting for a buffer to fill up.
This ensures that error messages are displayed as soon as they occur, which is useful for debugging.
Separate Stream:

cerr writes to the standard error stream (stderr), which is separate from the standard output stream (stdout) used by cout.
This allows you to redirect cout and cerr independently. For example:
./program > output.txt 2> error.txt
cout output goes to output.txt.
cerr output goes to error.txt.
Not Used for Input:

Unlike cin, cerr is not used for reading input. It is strictly for output.

*/