#include "PriorityQueue.h"

#include <iostream>
#include <stdexcept>

int PriorityQueue::parent(unsigned i) { return (i - 1) / 2; }

int PriorityQueue::left(unsigned i) {
    return (2 * i + 1) < m_size ? (2 * i + 1) : -1;
}

int PriorityQueue::right(unsigned i) {
    return (2 * i + 2) < m_size ? (2 * i + 2) : -1;
}

void PriorityQueue::swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

void PriorityQueue::heapify(unsigned i) {
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

void PriorityQueue::reserve(unsigned new_capacity) {
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

PriorityQueue::PriorityQueue(unsigned capacity) {
    m_capacity = capacity;
    m_size = 0;
    m_heap = new int[m_capacity];
}

PriorityQueue::PriorityQueue() {
    m_capacity = 50;
    m_size = 0;
    m_heap = new int[m_capacity];
}

PriorityQueue::~PriorityQueue() { delete[] m_heap; }

void PriorityQueue::insert(int key) {
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

void PriorityQueue::pop() {
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

int PriorityQueue::front() {
    // se a heap estiver vazia, lança uma exceção
    if (m_size == 0) {
        throw std::runtime_error("Empty queue");
    }
    return m_heap[0];  // retorna o elemento de maior prioridade
}

void PriorityQueue::print() {
    for (unsigned i = 0; i < m_size; ++i) {
        std::cout << m_heap[i] << " ";
    }
    std::cout << std::endl;
}

unsigned PriorityQueue::size() const { return m_size; }

bool PriorityQueue::empty() const { return m_size == 0; }