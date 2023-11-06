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

#ifndef PRIORITYQUEUEPAIR_H
#define PRIORITYQUEUEPAIR_H

#include <iostream>
#include <stdexcept>

/**
 * @brief Classe que implementa um iterador para a Priority Queue
 *
 */
/**
 * @brief Classe que implementa um iterador para a Priority Queue
 *
 * @tparam Type
 */
template <typename Type>
class PriorityQueuePairIterator {
   private:
    std::pair<int, Type>* m_ptr;

   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Type;
    using difference_type = std::ptrdiff_t;
    using pointer = Type*;
    using reference = Type&;

    PriorityQueuePairIterator(std::pair<int, Type>* ptr) : m_ptr(ptr) {}

    PriorityQueuePairIterator& operator++() {
        ++m_ptr;
        return *this;
    }

    PriorityQueuePairIterator operator++(int) {
        PriorityQueuePairIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    reference operator*() const { return m_ptr->second; }

    pointer operator->() const { return &(m_ptr->second); }

    bool operator==(const PriorityQueuePairIterator& other) const {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const PriorityQueuePairIterator& other) const {
        return !(*this == other);
    }
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
class PriorityQueuePair {
   private:
    // vetor que armazena os elementos da fila. O par consiste em um inteiro e
    // um Type, sendo o inteiro a prioridade do elemento
    std::pair<int, Type>* m_heap;
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
    void swap(std::pair<int, Type>* a, std::pair<int, Type>* b) {
        std::pair<int, Type> aux = *a;
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
        if (l != -1 && m_heap[l].first < m_heap[i].first) {
            smallest = l;
        }
        if (r != -1 && m_heap[r].first < m_heap[smallest].first) {
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
            std::pair<int, Type>* aux = new std::pair<int, Type>[new_capacity];
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
     * @brief Construtor da classe PriorityQueuePair
     * Complexidade: O(1)
     *
     * @param capacity
     */
    PriorityQueuePair(unsigned capacity) {
        m_capacity = capacity;
        m_size = 0;
        // cria um vetor de pares (prioridade, elemento)
        m_heap = new std::pair<int, Type>[m_capacity];
    }

    /**
     * @brief Construtor default da classe PriorityQueuePair. É aloca um vetor
     * de 50 posições. Complexidade: O(1)
     *
     */
    PriorityQueuePair() {
        m_capacity = 1;
        m_size = 0;
        m_heap = new std::pair<int, Type>[m_capacity];
    }

    /**
     * @brief Construtor de cópia da classe PriorityQueuePair.
     * Complexidade: O(n)
     *
     * @param pq PriorityQueuePair a ser copiada
     */
    PriorityQueuePair(const PriorityQueuePair& pq) {
        m_capacity = pq.m_capacity;
        m_size = pq.m_size;
        m_heap = new std::pair<int, Type>[m_capacity];
        for (unsigned i = 0; i < m_size; ++i) {
            m_heap[i] = pq.m_heap[i];
        }
    }

    /**
     * @brief Destrutor da classe PriorityQueuePair
     * Complexidade: O(1)
     *
     */
    ~PriorityQueuePair() { delete[] m_heap; }

    /**
     * @brief Função que insere um elemento na fila. O elemento é inserido no
     * final da heap. Logo após, a heap é corrigida.
     * Complexidade: O(n) / O(log n) amortizado
     *
     * @param key
     */
    void push(int key, const Type& value) {
        if (m_size == m_capacity) {
            reserve(2 * m_capacity);
        }
        m_heap[m_size] = std::make_pair(key, value);
        m_size++;
        unsigned i = m_size - 1;
        while (i > 0 && m_heap[parent(i)].first > m_heap[i].first) {
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
        if (m_size == 0) throw std::runtime_error("Empty queue");
        m_heap[0] = m_heap[m_size - 1];
        m_size--;
        heapify(0);
    }

    /**
     * @brief Função que retorna uma cópia para o primeiro elemento da fila
     * Complexidade: O(1)
     *
     * @return Type
     */
    Type& top() {
        // se a heap estiver vazia, lança uma exceção
        if (m_size == 0) throw std::runtime_error("Empty queue");
        return m_heap[0].second;
    }

    const Type& top() const {
        // se a heap estiver vazia, lança uma exceção
        if (m_size == 0) throw std::runtime_error("Empty queue");
        return m_heap[0].second;
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
            std::cout << (Type)m_heap[i].second << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Função que remove todos os elementos da fila: size() == 0
     * Complexidade: O(n)
     *
     */
    void clear() {
        while (m_size > 0) {
            pop();
        }
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

    using iterator = PriorityQueuePairIterator<Type>;

    /**
     * @brief Função que retorna o iterador para o primeiro elemento da fila
     * Complexidade: O(1)
     *
     * @return iteratorPQ
     */
    iterator begin() { return iterator(m_heap); }

    /**
     * @brief Função que retorna o iterador para o último elemento da fila
     * Complexidade: O(1)
     *
     * @return iteratorPQ
     */
    iterator end() { return iterator(m_heap + m_size); }
};

#endif  // PRIORITYQUEUEPAIR_H