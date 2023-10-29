/**
 * @file PriorityQueue.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Implementação de uma Priority Queue baseada em min heap
 * @version 0.1
 * @date 19-10-2023
 *
 *
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <stdexcept>

/**
 * @brief Classe que implementa um iterador para a Priority Queue
 *
 */
class iteratorPQ {
   private:
    int* m_ptr;  // ponteiro para o no atual

   public:
    /**
     * @brief Construct a new iterator P Q object
     * Complexidade: O(1)
     *
     * @param ptr
     */
    iteratorPQ(int* ptr) { m_ptr = ptr; }

    /**
     * @brief Sobrecarga do operador de pré-incremento.
     * Complexidade: O(1)
     *
     * @return iteratorPQ&
     */
    iteratorPQ& operator++() {
        m_ptr++;
        return *this;
    }

    /**
     * @brief Sobre carga do operador de pós-incremento.
     * Complexidade: O(1)
     *
     * @return iteratorPQ
     */
    iteratorPQ operator++(int) {
        iteratorPQ temp = *this;
        m_ptr++;
        return temp;
    }

    /**
     * @brief Sobrecarga do operador de indireção.
     * Complexidade: O(1)
     *
     * @return int&
     */
    int& operator*() { return *m_ptr; }

    /**
     * @brief Sobrecarga do operador de igualdade.
     * Complexidade: O(1)
     *
     * @param rhs
     * @return true
     * @return false
     */
    bool operator==(const iteratorPQ& rhs) { return m_ptr == rhs.m_ptr; }

    /**
     * @brief Sobrecarga do operador de diferença.
     * Complexidade: O(1)
     *
     * @param rhs
     * @return true
     * @return false
     */
    bool operator!=(const iteratorPQ& rhs) { return m_ptr != rhs.m_ptr; }
};

/**
 * @brief Classe que implementa uma Priority Queue baseada em min heap.
 *
 * Uma Priority Queue é uma estrutura de dados que mantém um conjunto de
 * elementos onde cada elemento possui uma prioridade associada, e a operação de
 * retirar um elemento da fila sempre remove o elemento de maior prioridade.
 * Neste caso, a Priority Queue é implementada como um min-heap, onde os
 * elementos de menor valor têm maior prioridade.
 *
 * @tparam Type
 */
template <typename Type>
class PriorityQueue {
   private:
    int* m_heap;
    unsigned m_size;
    unsigned m_capacity;

    /**
     * @brief Função que retorna o índice do pai de um nó
     * Complexidade: O(1)
     *
     * @param i
     * @return int
     */
    int parent(unsigned i) { return (i - 1) / 2; }

    /**
     * @brief Função que retorna o índice do filho esquerdo de um nó
     * Complexidade: O(1)
     *
     * @param i
     * @return int
     */
    int left(unsigned i) { return (2 * i + 1) < m_size ? (2 * i + 1) : -1; }

    /**
     * @brief Função que retorna o índice do filho direito de um nó
     * Complexidade: O(1)
     *
     * @param i
     * @return int
     */
    int right(unsigned i) { return (2 * i + 2) < m_size ? (2 * i + 2) : -1; }

    /**
     * @brief Função que troca o valor de dois nós
     * Complexidade: O(1)
     *
     * @param a
     * @param b
     */
    void swap(int* a, int* b) {
        int aux = *a;
        *a = *b;
        *b = aux;
    }

    /**
     * @brief Função que corrige a heap
     * Complexidade: O(log n)
     *
     * @param i
     */
    void heapify(unsigned i) {
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

    /**
     * @brief Função que aumenta a capacidade da fila. Se m_capacity >=
     * new_capacity, a funcao faz nada. Caso contrario, a funcao aumenta a
     * capacidade da fila para um valor maior ou igual a new_capacity.
     * Complexidade: O(n)
     *
     * @param new_capacity nova capacidade da fila
     */
    void reserve(unsigned new_capacity) {
        if (m_capacity < new_capacity) {
            int* aux = new int[new_capacity];        // aloca um novo vetor
            for (unsigned i = 0; i < m_size; ++i) {  // copia os elementos
                aux[i] = m_heap[i];
            }
            delete[] m_heap;  // libera o vetor antigo
            m_heap = aux;     // atualiza o ponteiro
            m_capacity = new_capacity;
        }
    }

   public:
    /**
     * @brief Construtor da classe PriorityQueue
     * Complexidade: O(1)
     *
     * @param capacity
     */
    PriorityQueue(unsigned capacity) {
        m_capacity = capacity;
        m_size = 0;
        m_heap = new int[m_capacity];
    }

    /**
     * @brief Construtor default da classe PriorityQueue. É aloca um vetor de 50
     * posições.
     * Complexidade: O(1)
     *
     */
    PriorityQueue() {
        m_capacity = 1;
        m_size = 0;
        m_heap = new int[m_capacity];
    }

    /**
     * @brief Construtor de cópia da classe PriorityQueue.
     * Complexidade: O(n)
     *
     * @param pq PriorityQueue a ser copiada
     */
    PriorityQueue(const PriorityQueue& pq) {
        m_capacity = pq.m_capacity;
        m_size = pq.m_size;
        m_heap = new int[m_capacity];
        for (unsigned i = 0; i < m_size; ++i) {
            m_heap[i] = pq.m_heap[i];
        }
    }

    /**
     * @brief Destrutor da classe PriorityQueue
     * Complexidade: O(1)
     *
     */
    ~PriorityQueue() { delete[] m_heap; }

    /**
     * @brief Função que insere um elemento na fila. O elemento é inserido no
     * final da heap. Logo após, a heap é corrigida.
     * Complexidade: O(n) / O(log n) amortizado
     *
     * @param key
     */
    void push(Type key) {
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

    /**
     * @brief Função que remove o elemento de maior prioridade da fila
     * Complexidade: O(log n)
     *
     */
    void pop() {
        // se a heap estiver vazia, lança uma exceção
        if (m_size == 0) throw std::runtime_error("Empty queue");
        // se a heap tiver apenas um elemento, remove-o
        if (m_size == 1) {
            m_size--;
            return;
        }

        m_heap[0] = m_heap[m_size - 1];  // copia o último elemento para a raiz
        m_size--;                        // decrementa o tamanho da heap
        heapify(0);                      // corrige a heap
    }

    /**
     * @brief Função que retorna uma cópia para o primeiro elemento da fila
     * Complexidade: O(1)
     *
     * @return Type
     */
    Type top() {
        // se a heap estiver vazia, lança uma exceção
        if (m_size == 0) throw std::runtime_error("Empty queue");
        return m_heap[0];  // retorna o elemento de maior prioridade
    }

    /**
     * @brief Função que imprime os elementos da fila na ordem em que estão no
     * vetor
     * Complexidade: O(n)
     *
     */
    void print() {
        if (m_size == 0) throw std::runtime_error("Empty queue");
        for (unsigned i = 0; i < m_size; ++i) {
            std::cout << (Type)m_heap[i] << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Função que retorna o tamanho da fila
     * Complexidade: O(1)
     *
     * @return int
     */
    unsigned size() const { return m_size; }

    /**
     * @brief Função que verifica se a fila está vazia
     * Complexidade: O(1)
     *
     * @return true
     * @return false
     */
    bool empty() const { return m_size == 0; }

    /**
     * @brief Função que retorna o iterador para o primeiro elemento da fila
     * Complexidade: O(1)
     *
     * @return iteratorPQ
     */
    iteratorPQ begin() { return iteratorPQ(m_heap); }

    /**
     * @brief Função que retorna o iterador para o último elemento da fila
     * Complexidade: O(1)
     *
     * @return iteratorPQ
     */
    iteratorPQ end() { return iteratorPQ(m_heap + m_size); }
};

#endif  // PRIORITYQUEUE_H