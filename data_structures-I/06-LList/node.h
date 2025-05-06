//*****************************************************************************************************
//
//      This header file defines a struct template that represents a node in a singly linked list.
//
//*****************************************************************************************************

#ifndef NODE_H
#define NODE_H

//*****************************************************************************************************

// Template struct for a node in a singly linked list
template <typename T>
struct Node {
    T data;          // Data stored in the node
    Node<T> *next;   // Pointer to the next node in the list

    Node();          // Default constructor
    Node(const T &d, Node<T> *n = nullptr); // Parameterized constructor
};

//*****************************************************************************************************

// Default constructor: initializes data to default value and next to nullptr
template <typename T>
Node<T>::Node() {
    data = T();     // Default initialization (e.g., 0 for numbers, empty string for strings)
    next = nullptr; // No next node
}

//*****************************************************************************************************

// Parameterized constructor: initializes data and sets the next pointer
template <typename T>
Node<T>::Node(const T &d, Node<T> *n) {
    data = d;       // Initialize data with the given value
    next = n;       // Set the next pointer
}

//*****************************************************************************************************

#endif