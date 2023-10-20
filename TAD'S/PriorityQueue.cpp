#include "PriorityQueue.h"

#include <iostream>
#include <stdexcept>

template <typename Type>
int PriorityQueue<Type>::parent(unsigned i) {
    return (i - 1) / 2;
}

template <typename Type>
int PriorityQueue<Type>::left(unsigned i) {
    return (2 * i + 1) < m_size ? (2 * i + 1) : -1;
}

template <typename Type>
int PriorityQueue<Type>::right(unsigned i) {
    return (2 * i + 2) < m_size ? (2 * i + 2) : -1;
}

template <typename Type>
void PriorityQueue<Type>::swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

template <typename Type>
void PriorityQueue<Type>::heapify(unsigned i) {
    int l = left(i);
    int r = right(i);
    unsigned smallest = i;
    if (l != -1 && m_heap[l] < m_heap[i]) {
        smallest = l;
    }
    if (r != -1 && m_heap[r] < m_heap[smallest]) {
        smallest = r;
    }
    if (smallest != i) {
        swap(&m_heap[i], &m_heap[smallest]);
        heapify(smallest);
    }
}

template <typename Type>
void PriorityQueue<Type>::reserve(unsigned new_capacity) {
    if (m_capacity < new_capacity) {
        m_capacity = new_capacity;
        int *aux = new int[m_capacity];          // aloca um novo vetor
        for (unsigned i = 0; i < m_size; ++i) {  // copia os elementos
            aux[i] = m_heap[i];
        }
        delete[] m_heap;  // libera o vetor antigo
        m_heap = aux;     // atualiza o ponteiro
    }
}

template <typename Type>
PriorityQueue<Type>::PriorityQueue(unsigned capacity) {
    m_capacity = capacity;
    m_size = 0;
    m_heap = new int[m_capacity];
}

template <typename Type>
PriorityQueue<Type>::PriorityQueue() {
    m_capacity = 50;
    m_size = 0;
    m_heap = new int[m_capacity];
}

template <typename Type>
PriorityQueue<Type>::~PriorityQueue() {
    delete[] m_heap;
}

template <typename Type>
void PriorityQueue<Type>::insert(Type key) {
    // se a heap estiver cheia, aumenta a capacidade
    if (m_size == m_capacity) {
        reserve(2 * m_capacity);
    }
    // insere o elemento na última posição
    m_heap[m_size] = key;
    m_size++;
    // corrige a heap
    int i = m_size - 1;
    while (i > 0 && m_heap[parent(i)] > m_heap[i]) {
        swap(&m_heap[i], &m_heap[parent(i)]);
        i = parent(i);
    }
}

template <typename Type>
void PriorityQueue<Type>::pop() {
    // se a heap estiver vazia, lança uma exceção
    if (m_size == 0) {
        throw std::runtime_error("Empty queue");
    }
    // se a heap tiver apenas um elemento, remove-o
    if (m_size == 1) {
        m_size--;
        return;
    }

    m_heap[0] = m_heap[m_size - 1];  // copia o último elemento para a raiz
    m_size--;                        // decrementa o tamanho da heap
    heapify(0);                      // corrige a heap
}

template <typename Type>
Type PriorityQueue<Type>::front() {
    // se a heap estiver vazia, lança uma exceção
    if (m_size == 0) {
        throw std::runtime_error("Empty queue");
    }
    return m_heap[0];  // retorna o elemento de maior prioridade
}

template <typename Type>
void PriorityQueue<Type>::print() {
    for (unsigned i = 0; i < m_size; ++i) {
        std::cout << (Type)m_heap[i] << " ";
    }
    std::cout << std::endl;
}

template <typename Type>
unsigned PriorityQueue<Type>::size() const {
    return m_size;
}

template <typename Type>
bool PriorityQueue<Type>::empty() const {
    return m_size == 0;
}