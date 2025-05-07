#include "practice_queue.h"
#include <iostream>
using namespace std;

void displayQueue(bool success, Queue<short> &shortQueue);
void checkState(Queue<short> &shortQueue);

int main(){
    Queue<short> shortQueue;
    short num;
    bool success;

    checkState(shortQueue);
    for (int i = 0; i < 10; ++i){
        num = 10 * (i+1);
        success = shortQueue.enqueue(num);
        if (success)
            cout << "enqueue: " << num << endl;
        displayQueue(success, shortQueue);
    }
    cout << endl;
    for (int i = 0; i < 10; ++i){
        success = shortQueue.dequeue(num);
        if (success)
            cout << "dequeue: " << num << endl;
        displayQueue(success, shortQueue);
    }

    return 0;
}

void displayQueue(bool success, Queue<short> &shortQueue){
    short front, back;
    int numVal;
    if (success){
        numVal = shortQueue.getNumValues();
        shortQueue.viewFront(front);
        shortQueue.viewRear(back);
        if (numVal > 0){
            cout << "numValues: " << numVal << "\tfront: " << front << "\tback: " << back << endl;
        } else {
            cout << "numValues: " << numVal << endl;
        }
    }
    checkState(shortQueue);
}

void checkState(Queue<short> &shortQueue){
    if (shortQueue.isEmpty())
        cout << "\nqueue is empty\n\n";
    else if (shortQueue.isFull())
        cout << "\nqueue is full\n\n";
}