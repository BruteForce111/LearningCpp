//*****************************************************************************************************
//
//      This header file defines a class template for a singly linked list.
//
//      Other files required:
//        1.	 node.h - header file for the AList class
//
//*****************************************************************************************************

#ifndef LLIST_H
#define LLIST_H

//*****************************************************************************************************

#include "node.h"
#include <iostream>
#include <new>

//*****************************************************************************************************

// Template class for a singly linked list
template <typename T>
class LList {
private:
    Node<T> *front; // Pointer to the first node in the list

public:
    LList();  // Constructor
    ~LList(); // Destructor

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

//*****************************************************************************************************

// Constructor: initializes the list to be empty
template <typename T>
LList<T>::LList() {
    front = nullptr;
}

//*****************************************************************************************************

// Destructor: deletes all nodes in the list
template <typename T>
LList<T>::~LList() {
    Node<T> *pCur = nullptr;

    while (front) {
        pCur = front;         // Point to the current node
        front = front->next;  // Move to the next node
        delete pCur;          // Delete the current node
    }
}

//*****************************************************************************************************

// Insert a value into the list in sorted order
template <typename T>
bool LList<T>::insert(const T &dataIn) {
    bool success = false;
    Node<T> *pBefore = nullptr; // Pointer to the node before the insertion point
    Node<T> *pCur = front;      // Pointer to traverse the list
    Node<T> *pNew;              // Pointer to the new node

    // Find the insertion point
    while ((pCur) && (pCur->data < dataIn)) {
        pBefore = pCur;
        pCur = pCur->next;
    }

    // Create a new node
    pNew = new (std::nothrow) Node<T>(dataIn, pCur);

    if (pNew) {
        if (pBefore)
            pBefore->next = pNew; // Insert after pBefore
        else
            front = pNew;         // Insert at the front

        success = true;
    }

    return success;
}

//*****************************************************************************************************

// Remove a value from the list
template <typename T>
bool LList<T>::remove(T &dataOut) {
    bool success = false;
    Node<T> *pBefore = nullptr; // Pointer to the node before the target
    Node<T> *pCur = front;      // Pointer to traverse the list

    // Find the target node
    while ((pCur) && (pCur->data < dataOut)) {
        pBefore = pCur;
        pCur = pCur->next;
    }

    // If the target node is found
    if ((pCur) && (pCur->data == dataOut)) {
        dataOut = pCur->data; // Copy the data to dataOut

        if (pBefore)
            pBefore->next = pCur->next; // Remove the node from the middle
        else
            front = pCur->next;         // Remove the front node

        delete pCur; // Delete the node
        success = true;
    }

    return success;
}

//*****************************************************************************************************

// Retrieve a value from the list
template <typename T>
bool LList<T>::retrieve(T &dataOut) const {
    bool success = false;
    Node<T> *pCur = front; // Pointer to traverse the list

    // Find the target node
    while ((pCur) && (pCur->data < dataOut))
        pCur = pCur->next;

    // If the target node is found
    if ((pCur) && (pCur->data == dataOut)) {
        dataOut = pCur->data; // Copy the data to dataOut
        success = true;
    }

    return success;
}

//*****************************************************************************************************

// View the first value in the list
template <typename T>
bool LList<T>::viewFront(T &dataOut) const {
    bool success = false;

    if (front) {
        dataOut = front->data; // Copy the front value to dataOut
        success = true;
    } 

    return success;
}

//*****************************************************************************************************

// View the last value in the list
template <typename T>
bool LList<T>::viewRear(T &dataOut) const {
    bool success = false;
    Node<T> *pCur = front; // Pointer to traverse the list

    // Traverse to the last node
    while ((pCur) && (pCur->next))
        pCur = pCur->next;

    if (pCur) {
        dataOut = pCur->data; // Copy the rear value to dataOut
        success = true;
    } 

    return success;
}

//*****************************************************************************************************

// Display the contents of the list
template <typename T>
void LList<T>::display() const {
    Node<T> *pCur = front; // Pointer to traverse the list

    while (pCur) {
        std::cout << pCur->data;

        if (pCur->next)
            std::cout << " -> "; // Print arrow if there is a next node

        pCur = pCur->next;
    }

    std::cout << std::endl;
}

//*****************************************************************************************************

// Get the number of values in the list
template <typename T>
int LList<T>::getNumValues() const {
    int numVal = 0;
    Node<T> *pCur = front; // Pointer to traverse the list

    while (pCur) {
        numVal++;          // Increment the count
        pCur = pCur->next; // Move to the next node
    }

    return numVal;
}

//*****************************************************************************************************

// Check if the list is empty
template <typename T>
bool LList<T>::isEmpty() const {
    return (front == nullptr); // True if front is null
}

//*****************************************************************************************************

// Check if the list is full
template <typename T>
bool LList<T>::isFull() const {
    bool success = true;
    Node<T> *pNew = nullptr;

    // Try to allocate a new node
    pNew = new (std::nothrow) Node<T>;

    if (pNew) {
        delete pNew; // Free the allocated memory
        success = false; // List is not full
    }

    return success;
}

//*****************************************************************************************************

#endif