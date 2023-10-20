#include "Queue.h"

template <typename Type>
iterator_queue<Type>::iterator_queue(Node<Type> *ptr) {
    m_ptr = ptr;
}

template <typename Type>
iterator_queue<Type> &iterator_queue<Type>::operator++() {
    m_ptr = m_ptr->next;
    return *this;
}

template <typename Type>
iterator_queue<Type> iterator_queue<Type>::operator++(int) {
    iterator_queue temp = *this;
    m_ptr = m_ptr->next;
    return temp;
}

template <typename Type>
Type &iterator_queue<Type>::operator*() {
    return m_ptr->data;
}

template <typename Type>
bool iterator_queue<Type>::operator==(const iterator_queue &other) {
    return m_ptr == other.m_ptr;
}

template <typename Type>
bool iterator_queue<Type>::operator!=(const iterator_queue &other) {
    return m_ptr != other.m_ptr;
}

template <typename Type>
Queue<Type>::Queue() {
    m_head = new Node<Type>(Type(), nullptr);
    m_tail = m_head;
    m_size = 0;
}

template <typename Type>
Queue<Type>::Queue(const Queue &lst) {
    m_head = new Node<Type>(Type(), nullptr);
    Node<Type> *aux = lst.m_head;
    while (aux != nullptr) {
        push(aux->data);
        aux = aux->next;
    }
    m_size = lst.m_size;
}

template <typename Type>
Queue<Type>::~Queue() {
    delete m_head;
}

template <typename Type>
bool Queue<Type>::empty() const {
    return m_size == 0;
}

template <typename Type>
unsigned int Queue<Type>::size() const {
    return m_size;
}

template <typename Type>
void Queue<Type>::clear() {
    delete m_head;
}

template <typename Type>
void Queue<Type>::push(const int &val) {
    Node<Type> *aux = new Node<Type>(val, nullptr);
    if (m_size > 0) {
        m_tail->next = aux;
        m_tail = aux;
    } else {
        m_tail = m_head = aux;
    }
    m_size++;
}

template <typename Type>
int &Queue<Type>::front() {
    if (m_size == 0) throw std::runtime_error("empty queue");
    return m_head->data;
}

template <typename Type>
const int &Queue<Type>::front() const {
    if (m_size == 0) throw std::runtime_error("empty queue");
    return m_head->data;
}

template <typename Type>
void Queue<Type>::pop() {
    if (m_size == 0) throw std::runtime_error(" empty queue ");
    Node<Type> *aux = m_head;
    m_head = aux->next;
    aux->next = nullptr;
    delete aux;
    m_size--;
}

template <typename Type>
int &Queue<Type>::back() {
    if (m_size == 0) throw std::runtime_error("empty queue");
    return m_tail->data;
}

template <typename Type>
const int &Queue<Type>::back() const {
    if (m_size == 0) throw std::runtime_error("empty queue");
    return m_tail->data;
}

template <typename Type>
iterator_queue<Type> Queue<Type>::begin() {
    return iterator_queue<Type>(m_head);
}

template <typename Type>
iterator_queue<Type> Queue<Type>::end() {
    return iterator_queue<Type>(m_tail->next);
}
