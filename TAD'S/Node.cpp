#include "Node.h"

template <typename Type>
Node<Type>::Node(Type data, Node *next) {
    this->data = data;
    this->next = next;
}

template <typename Type>
Node<Type>::~Node() {
    delete next;
}