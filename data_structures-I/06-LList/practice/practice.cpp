//*****************************************************************************************************
//
//      This program demonstrates the use of the LList class by instantiating a singly linked shortList of
//      short integers and performing its methods.
//
//      Other files required:
//        1.	 LList.h - header file for the LList class
//
//*****************************************************************************************************

#include "practice_LList.h"

#include <iostream>
using namespace std;

//*****************************************************************************************************

// Function to display the linked list and its state
void displayLList(bool success, LList<short> &shortList);

// Function to check if the linked list is empty or full
void checkState(LList<short> &shortList);

//*****************************************************************************************************

int main() {
    LList<short> shortList; // Create a linked list of short integers
    bool success;           // To store the success status of operations
    short num;              // Variable to hold data for operations

    // Check and display the initial state of the list
    checkState(shortList);

    // Insert 5 elements into the list
    for (int i = 0; i < 5; ++i) {
        num = 10 * (i + 1); // Generate numbers 10, 20, 30, 40, 50
        success = shortList.insert(num); // Insert the number into the list

        if (success)
            cout << "inserted " << num << endl;

        displayLList(success, shortList); // Display the list after each insertion
    }

    cout << endl;

    // Retrieve (search for) the first two elements (10 and 20)
    for (int i = 0; i < 2; ++i) {
        num = 10 * (i + 1); // Numbers 10 and 20
        success = shortList.retrieve(num); // Check if the number exists in the list

        if (success)
            cout << "retrieved " << num << endl;

        displayLList(success, shortList); // Display the list after each retrieval
    }

    cout << endl;

    // Remove all elements from the list in reverse order (50, 40, ..., 10)
    for (int i = 0; i < 5; ++i) {
        num = (10 * (5 - i)); // Numbers 50, 40, 30, 20, 10
        success = shortList.remove(num); // Remove the number from the list

        if (success)
            cout << "removed " << num << endl;

        displayLList(success, shortList); // Display the list after each removal
    }

    return 0;
}

//*****************************************************************************************************

// Display the linked list and its state
void displayLList(bool success, LList<short> &shortList) {
    short front, rear; // Variables to hold the front and rear values
    int numVal;        // Variable to hold the number of values in the list

    if (success) {
        shortList.display(); // Display the contents of the list
        shortList.viewFront(front); // Get the front value
        shortList.viewRear(rear);   // Get the rear value
        numVal = shortList.getNumValues(); // Get the number of values in the list

        if (numVal > 0)
            cout << "numValues: " << numVal
                 << "\tfront: " << front
                 << "\trear: " << rear << endl;
        else
            cout << "numValues: " << numVal << endl;
    }

    checkState(shortList); // Check if the list is empty or full
}

//*****************************************************************************************************

// Check if the linked list is empty or full
void checkState(LList<short> &shortList) {
    if (shortList.isFull())
        cout << "\nlist is full\n\n";
    else if (shortList.isEmpty())
        cout << "\nlist is empty\n\n";
}

//*****************************************************************************************************
/*

list is empty 

inserted 10
10
numValues: 1    front: 10       rear: 10
inserted 20
10 -> 20
numValues: 2    front: 10       rear: 20
inserted 30
10 -> 20 -> 30
numValues: 3    front: 10       rear: 30
inserted 40
10 -> 20 -> 30 -> 40
numValues: 4    front: 10       rear: 40
inserted 50
10 -> 20 -> 30 -> 40 -> 50
numValues: 5    front: 10       rear: 50

retrieved 10
10 -> 20 -> 30 -> 40 -> 50
numValues: 5    front: 10       rear: 50
retrieved 20
10 -> 20 -> 30 -> 40 -> 50
numValues: 5    front: 10       rear: 50

removed 50
10 -> 20 -> 30 -> 40
numValues: 4    front: 10       rear: 40
removed 40
10 -> 20 -> 30
numValues: 3    front: 10       rear: 30
removed 30
10 -> 20
numValues: 2    front: 10       rear: 20
removed 20
10
numValues: 1    front: 10       rear: 10
removed 10

numValues: 0

list is empty

*/