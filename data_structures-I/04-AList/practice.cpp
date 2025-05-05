#include "practice.h"
#include <iostream>

using namespace std;

void checkState(AList<short> &shortList);
void displayAList(bool success, AList<short> &shortList);

int main(){
    AList<short> shortList(3);
    short        num;         // value to insert
    int          i = 0;       // index for insertAtIndex
    bool         success;     // result of each operation

    // Report initial state (empty or full)
    checkState(shortList);

    // 1) Insert 10 at the front of the list
    num = 50;
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

}

void displayAList(bool success, AList<short> &shortList) {
    short min;
    int cap, numVal;
    if (success){
        shortList.display();
        shortList.getSmallest(min);
        cap = shortList.getCapacity();
        numVal = shortList.getNumValues();

        if (numVal > 0)
            cout << "capacity: " << cap << "\tnumVal: " << numVal << "\tsmallest: " << min << endl;
        else 
            cout << "capacity: " << cap << "\tnumValues: " << numVal << endl;
        cout << endl; 
    }
    checkState(shortList);
}

void checkState(AList<short> &shortList){
    if (shortList.isFull())
        cerr << "list is full\n\n";
    else if (shortList.isEmpty())
        cerr << "list is empty\n\n";
}