#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T> *next;
    
    Node();
    Node(const T &d, Node<T> *n = nullptr);
};

template <typename T>
Node<T>::Node() {
    data = T();
    next = nullptr;
}

template <typename T>
Node<T>::Node(const T &d, Node<T> *n) {
    data = d;
    next = n;
} 

#endif // NODE_H