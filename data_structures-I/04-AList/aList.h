//*****************************************************************************************************
//
//      This header file defines a class template for an array-based list.
//
//*****************************************************************************************************

#ifndef ALIST_H
#define ALIST_H

//*****************************************************************************************************

#include <iostream>   // for std::cout, std::endl
#include <new>        // for std::nothrow

//*****************************************************************************************************

template <typename T>
class AList {
private:
    T *list;           // pointer to dynamic array holding the elements
    int capacity;      // total allocated slots in 'list'
    int numValues;     // current number of stored elements

    // Double the capacity when we run out of room; returns true on success
    bool _resize();

public:
    // Constructor: allocate an array of size 'cap' (minimum 2), start empty
    AList(int cap = 5); // This means if no capacity is provided, the list will default to a capacity of 5.
                        // if no initialization, you must explicitly provide the capacity when creating an AList object.

    // Destructor: free the dynamic array
    ~AList();

    // Insert at front (shifts existing elements right)
    bool insertFront(const T &dataIn);

    // Insert at back (append)
    bool insertBack(const T &dataIn);

    // Insert at given index (0 <= index <= numValues), shifts elements right
    bool insertAtIndex(const T &dataIn, int index);

    // Print all elements to std::cout; returns false if empty
    bool display() const;

    // Find the smallest element (uses operator<) and write it to dataOut
    bool getSmallest(T &dataOut) const;

    // Accessors
    int getCapacity() const;   // how many slots allocated
    int getNumValues() const;  // how many slots in use

    // Checks
    bool isEmpty() const;      // true if no elements
    bool isFull() const;       // true if numValues == capacity
};

//*****************************************************************************************************

template <typename T>
AList<T>::AList(int cap) {
    if (cap < 2)
        cap = 2;              // enforce minimum capacity of 2

    capacity = cap;           // set the allocated size
    numValues = 0;            // start with no elements
    list = new T[capacity];   // allocate array of T[capacity]
}

//*****************************************************************************************************

template <typename T>
AList<T>::~AList() {
    delete[] list;            // free the dynamic array
    list = nullptr;           // avoid dangling pointer
    capacity = 0;
    numValues = 0;
}

//*****************************************************************************************************

template <typename T>
bool AList<T>::_resize() {
    bool success = false;
    int newCapacity = capacity * 2;                       // double the capacity
    T *newList = new (std::nothrow) T[newCapacity];       // allocate, or nullptr on failure
                                                          // nothrow usually used with new[] to avoid exceptions

    if (newList) {                                        // if allocation succeeded
        for (int i = 0; i < numValues; ++i)
            newList[i] = list[i];                        // copy existing elements

        delete[] list;                                   // free old array
        list = newList;                                  // point to the new larger array
        capacity = newCapacity;                          // update capacity
        success = true;
    }

    return success;                                       // true if resized, false if malloc failed
}

//*****************************************************************************************************

template <typename T>
bool AList<T>::insertFront(const T &dataIn) {
    bool success = true;

    if (numValues == capacity)                             // need more room?
        success = _resize();                              // attempt to grow array

    if (success) {
        // shift all elements one slot to the right, from back to front
        for (int i = numValues; i > 0; i--)
            list[i] = list[i - 1];

        list[0] = dataIn;                                  // place new element at index 0
        numValues++;                                       // increment count
    }

    return success;                                        // false if resizing failed
}

//*****************************************************************************************************

template <typename T>
bool AList<T>::insertBack(const T &dataIn) {
    bool success = true;

    if (numValues == capacity)                             // if full, grow
        success = _resize();

    if (success) {
        list[numValues] = dataIn;                         // append at end
        numValues++;                                      // update count
    }

    return success;
}

//*****************************************************************************************************

template <typename T>
bool AList<T>::insertAtIndex(const T &dataIn, int index) {
    bool success = false;

    // valid if index in [0..numValues]
    if ((index >= 0) && (index <= numValues)) {
        success = true;
        if (numValues == capacity)                         // resize if needed
            success = _resize();

        if (success) {
            // shift elements right starting from 'index'
            for (int i = numValues; i > index; --i)
                list[i] = list[i - 1];

            list[index] = dataIn;                         // insert new element
            numValues++;                                  // update count
        }
    }

    return success;                                       // false if out of range or resize failed
}

//*****************************************************************************************************

template <typename T>
bool AList<T>::display() const {
    bool success = false;

    if (numValues > 0) {
        for (int i = 0; i < numValues; ++i)
            std::cout << "[" << i << "] " << list[i] << std::endl;
        success = true;
    }
    return success;                                       // false if list is empty
}

//*****************************************************************************************************

template <typename T>
bool AList<T>::getSmallest(T &dataOut) const {
    bool success = false;

    if (numValues > 0) {
        dataOut = list[0];                                // start with the first element
        // scan remaining elements for a smaller one
        for (int i = 1; i < numValues; ++i)
            if (list[i] < dataOut)
                dataOut = list[i];
        success = true;
    }
    return success;                                       // false if list is empty
}

//*****************************************************************************************************

template <typename T>
int AList<T>::getCapacity() const {
    return capacity;                                      // total slots allocated
}

//*****************************************************************************************************

template <typename T>
int AList<T>::getNumValues() const {
    return numValues;                                     // how many used slots
}

//*****************************************************************************************************

template <typename T>
bool AList<T>::isEmpty() const {
    return (numValues == 0);                              // true if nothing stored
}

//*****************************************************************************************************

template <typename T>
bool AList<T>::isFull() const {
    return (numValues == capacity);                       // true if at capacity
}

//*****************************************************************************************************

#endif  // ALIST_H
