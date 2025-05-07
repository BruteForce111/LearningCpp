#include "practice.h"
#include <iostream>
using namespace std;

void checkState(Stack<short> &stack);
void displayStack(bool success, Stack<short> &stack);

int main(){
    Stack<short> shortStack(10);
    short num;
    bool success;
    
    checkState(shortStack);
    for (int i = 0; i < 10; ++i){
        num = 10 * (i+1);
        success = shortStack.push(num);

        if (success)
            cout<< "pushed: " << num << endl;
        
        displayStack(success, shortStack);
    }

    for (int i = 0; i < 10; ++i){
        success = shortStack.pop(num);
        if (success)
            cout << "popped: " << num << endl;
        
        displayStack(success, shortStack);
    }
    return 0;
}

void displayStack(bool success, Stack<short> &stack){
    short num;
    int numVal;
    if (success){
        numVal = stack.getNumValues();
        stack.peek(num);
        if (numVal > 0) 
            cout << "numValues: " << numVal << "\tpeeked: " << num << endl;
        else
            cout << "numValues: " << numVal << endl;
    }
    checkState(stack);
}

void checkState(Stack<short> &stack){
    if (stack.isFull())
        cerr << "\nstack is full\n\n";
    else if (stack.isEmpty())
        cerr << "\nstack is empty\n\n";
}