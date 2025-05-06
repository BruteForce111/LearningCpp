#ifndef LLIST_H
#define LLIST_H

#include "practice_Node.h"
#include <iostream>
#include <new>

template <typename T>
class LList {
private:
    Node<T> *front;

public:
    LList();
    ~LList();
    
    // Member functions
    bool insert(const T &dataIn);  // Insert a value into the list in sorted order
    bool remove(T &dataOut);       // Remove a value from the list
    bool retrieve(T &dataOut) const; // Retrieve a value from the list
    bool viewFront(T &dataOut) const; // View the first value in the list
    bool viewRear(T &dataOut) const;  // View the last value in the list
    void display() const;          // Display the contents of the list
    int getNumValues() const;      // Get the number of values in the list
    bool isEmpty() const;          // Check if the list is empty
    bool isFull() const;           // Check if the list is full
    
};

template <typename T>
LList<T>::LList(){
    front = nullptr;
}

template <typename T>
LList<T>::~LList(){
    Node<T>* pCur;
    while (front){
        pCur = front;
        front = front->next;
        delete pCur;
    }
}


template <typename T>
bool LList<T>::insert(const T &dataIn){
    bool success = false;
    Node<T>* pBefore = nullptr;
    Node<T>* pCur = front;
    Node<T>* pNew;

    while (pCur && (pCur->data < dataIn)){
        pBefore = pCur;
        pCur = pCur->next;
    }
    pNew = new (std::nothrow) Node<T>(dataIn, pCur);
    if (pNew){
        if (pBefore)
            pBefore->next = pNew;
        else 
            front = pNew;
        success = true;
    }
    return success;
}


// Remove a value from a List
template <typename T>
bool LList<T>::remove(T &dataOut){
    bool success = false;
    Node<T> *pBefore = nullptr;
    Node<T>* pCur = front;

    while (pCur && pCur->data < dataOut){
        pBefore = pCur;
        pCur = pCur->next;
    }

    if ((pCur) && (pCur->data == dataOut)) {
        dataOut = pCur->data;
        if (pBefore)
            pBefore->next = pCur->next;
        else
            front = pCur->next;
        
        delete pCur;
        success = true;
    }
    return success;
}

// Retrieve a value from the list
template <typename T>
bool LList<T>::retrieve(T &dataOut) const {
    bool success = false;
    Node<T>* pCur = front;
    while (pCur && (pCur->data < dataOut)){
        pCur = pCur->next;
    }
    if (pCur && (pCur->data == dataOut)){
        dataOut = pCur->data;
        success = true;
    }
    return success;
}

template <typename T>
bool LList<T>::viewFront(T &dataOut) const{
    bool success = false;
    if (front){
        dataOut = front->data;
        success = true;
    }
    return success;
}

template <typename T>
//trailing const here is not to modify members(Node<T>* front) of object viewRear of class LList
bool LList<T>::viewRear(T &dataOut) const {
    bool success = false;
    Node<T>* pCur = front;
    while (pCur && pCur->next){
        pCur = pCur->next;
    }
    if (pCur){
        dataOut = pCur->data;
        success = true;
    }

    return success;
}

template <typename T>
void LList<T>::display() const {
    Node<T> *pCur = front;
    while (pCur){
        std::cout << pCur->data;
        if (pCur->next)
            std::cout << " -> ";
        
        pCur = pCur->next;
    }
    std::cout << std::endl;
}         

template <typename T>
int LList<T>::getNumValues() const {
    int num = 0;
    Node<T>* pCur = front;
    while (pCur){
        num += 1;
        pCur = pCur->next;
    }
    return num;
}

template <typename T>
bool LList<T>::isEmpty() const {
    return (front) ? true : false;
}   

// it is full in hard memory not capacity itself in this code
template <typename T>
bool LList<T>::isFull() const {
    bool full = true;
    Node<T> *pNew = nullptr;
    pNew = new (std::nothrow) Node<T>;
    if (pNew){
        delete pNew;
        full = false;
    }
    return full;
}     

#endif // LList_H