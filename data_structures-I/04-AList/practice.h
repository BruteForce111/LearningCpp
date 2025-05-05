#ifndef PRACTICE_H
#define PRACTICE_H

#include <iostream>
using namespace std;

template <typename T>
class AList {
private:
    T* list;
    int capacity;
    int numValues;

    bool _resize();

public:
    // Constructor
    AList(int cap =  5);

    // Destructor
    ~AList();

    // insertFront
    bool insertFront(const T &dataIn);

    //insertBack
    bool insertBack(const T &dataIn);

    //insertAtIndex
    bool insertAtIndex(const T &dataIn, int index);

    //display
    // display all elements in AList, return false if empty
    bool display() const;

    //getSmallest
    bool getSmallest(T &dataOut) const;

    //Accessor: getCapacity
    int getCapacity() const;

    //Accessor: getNumValues
    int getNumValues() const;

    //check Full or Empty
    bool isFull() const;
    bool isEmpty() const;
};

//Function implementation

//Constructor
template <typename T>
AList<T>::AList (int cap) {
    if (cap < 2)
        cap = 2;
    capacity = cap;
    numValues = 0;
    list = new T[capacity];
}

//Destructor
template <typename T>
AList<T>::~AList (){
    delete[] list;
    list = nullptr;
    numValues = 0;
    capacity = 0;
}

// resize function
template <typename T>
bool AList<T>::_resize(){
    bool success = false;
    int newCapacity = 2 * capacity;
    T* newList = new T[newCapacity];
    if (newList){
        for (int i = 0; i < numValues; i++){
            newList[i] = list[i];
        }
        delete[] list;
        list = newList;
        capacity = newCapacity;
        success = true;
    }
    return success;
}

// insertFront
template <typename T>
bool AList<T>::insertFront (const T &dataIn){
    bool success = true;
    if (numValues == capacity)
        success = _resize();
    
    if (success) {
        for (int i = numValues; i > 0; i--){
            list[i] = list[i-1];
        }
        list[0] = dataIn;
        numValues++;
    }
    return success;
}

// insertBack
template <typename T>
bool AList<T>::insertBack (const T &dataIn){
    bool success = true;
    if (numValues == capacity){
        success = _resize();
    }
    if (success){
        list[numValues] = dataIn;
        numValues++;   
    }
    return success;
}

// insertAtIndex
template <typename T>
bool AList<T>::insertAtIndex(const T &dataIn, int index){
    bool success = false;
    
    if (index >= 0 && index <= numValues){
        success = true;
        if (numValues == capacity){
            success = _resize();
        }
        if (success){
            for (int i = numValues; i > index; i--){
                list[i] = list[i-1];
            }
            list[index] = dataIn;
            numValues++;    
        }
    }
    return success;
}


//display
// display all elements in AList, return false if empty
template <typename T>
bool AList<T>::display() const {
    bool success = false;
    if (numValues > 0){
        success = true;
        for (int i = 0; i < numValues; i++){
            cout << "[" << i << "] " << list[i] << endl;
        }
    }
    return success;
}

//getSmallest
template <typename T>
bool AList<T>::getSmallest(T &dataOut) const{
    bool success = false;
    if (numValues > 0){
        success = true;
        dataOut = list[0];
        for (int i = 1; i < numValues; i++){
            if (list[i] < dataOut) {
                dataOut = list[i];
            }
        }
    }
    return success;
}

//Accessor: getCapacity
template <typename T>
int AList<T>::getCapacity() const {
    return capacity;
}

//Accessor: getNumValues
template <typename T>
int AList<T>::getNumValues() const{
    return numValues;
}

//check Full or Empty
template <typename T>
bool AList<T>::isFull() const{
    return numValues == capacity;
}

template <typename T>
bool AList<T>::isEmpty() const{
    return numValues == 0;
}

//

#endif // PRACTICE_H