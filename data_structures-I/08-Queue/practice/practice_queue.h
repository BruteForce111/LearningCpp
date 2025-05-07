#ifndef PRACTICE_QUEUE_H
#define PRACTICE_QUEUE_H

#include "practice_node.h"
#include <new>

template <typename T>
class Queue {
private:
    Node<T> *front;
    Node<T> *back;
    int numValues;

public:
    Queue();
    ~Queue();
    bool enqueue(const T &dataIn);
    bool dequeue(T &dataOut);
    bool viewFront(T &dataOut) const;
    bool viewRear(T &dataOut) const;
    int getNumValues() const;
    bool isFull() const;
    bool isEmpty() const;
};

template <typename T>
Queue<T>::Queue(){
    front = nullptr;
    back = nullptr;
    numValues = 0;
}

template <typename T>
Queue<T>::~Queue(){
    Node<T>* pCur = nullptr;
    while (front){
        pCur = front;
        front = front->next;
        delete pCur;
    }
    back = nullptr;
    numValues = 0;
}

template <typename T>
bool Queue<T>::enqueue(const T &dataIn){
    bool success = false;
    Node<T>* pNew = new (std::nothrow) Node<T>(dataIn);
    if (pNew){
        if (back){
            back->next = pNew;
        } else {
            front = pNew;
        }
        back = pNew;
        numValues++;
        success = true;
    }
    return success;
}

template <typename T>
bool Queue<T>::dequeue(T &dataOut){
    bool success = false;
    Node<T>* pCur = front;
    if (front){
        dataOut = front->data;
        front = front->next;
        delete pCur;
        numValues--;
        if (numValues == 0){
            back = nullptr;
        }
        success = true;
    }
    return success;
}

template <typename T>
bool Queue<T>::viewFront(T &dataOut) const{
    bool success = false;
    if (front){
        dataOut = front->data;
        success = true;
    }
    return success;
}

template <typename T>
bool Queue<T>::viewRear(T &dataOut) const{
    bool success = false;
    if (back){
        dataOut = back->data;
        success = true;
    }
    return success;
}

template <typename T>
int Queue<T>::getNumValues() const{
    return numValues;
}

template <typename T>
bool Queue<T>::isFull() const{
    bool full = true;
    Node<T>* pNew = new (std::nothrow) Node<T>; //is this dangerous
    if (pNew){
        delete pNew;
        full = false;
    }
    return full;
}

template <typename T>
bool Queue<T>::isEmpty() const{
    return (numValues == 0);
}


#endif // PRACTICE_QUEUE_H