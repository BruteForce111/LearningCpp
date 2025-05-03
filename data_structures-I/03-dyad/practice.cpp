#include "practice.h"
#include <iostream>

using namespace std;

int main(){
    int firstInt, secondInt;
    double firstDouble, secondDouble;
    char firstChar, secondChar;
    
    // Create instances/objects from the class first
    Dyad<int> DyadInt(1, 4);
    Dyad<double> DyadDouble(2.9, 5.6);
    Dyad<char> DyadChar('f', 's');
    
    // Print first Int and second Int -> swap -> get two values
    
    cout << "First Int: " << DyadInt.getFirst() << "\n" << "Second Int: " << DyadInt.getSecond() << "\n";

    DyadInt.swapValues();
    DyadInt.get2Values(firstInt, secondInt);

    cout << "First Int after swapping: " << firstInt << "\n" << "Second Int after swapping: " << secondInt << "\n";
    // Print first Double and second Double -> swap -> get two values

    cout << "First Double: " << DyadDouble.getFirst() << "\n" << "Second Double: " << DyadDouble.getSecond() << "\n";

    DyadDouble.swapValues();
    DyadDouble.get2Values(firstDouble, secondDouble);  
    
    cout << "First Double after swapping: " << firstDouble << "\n" << "Second Double after swapping: " << secondDouble << "\n";

    // Print first Char and second Char -> swap -> get two values;
    
    cout << "First Char: " << DyadChar.getFirst() << "\n" << "Second Char: " << DyadChar.getSecond() << "\n";

    DyadChar.swapValues();
    DyadChar.get2Values(firstChar, secondChar);  
    
    cout << "First Char after swapping: " << firstChar << "\n" << "Second Char after swapping: " << secondChar << "\n";
}
