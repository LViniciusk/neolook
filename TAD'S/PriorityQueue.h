/**
 * @file PriorityQueue.h
 * @author Júnior Silva (junior.silva@alu.ufc.br)
 * @author Linyker Vinicius (botlink2030@alu.ufc.br)
 * @brief Implementação de uma Priority Queue baseada em min heap
 * @version 0.1
 * @date 19-10-2023
 *
 *
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

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
     *
     * @param i
     * @return int
     */
    int parent(unsigned i) { return (i - 1) / 2; }

    /**
     * @brief Função que retorna o índice do filho esquerdo de um nó
     *
     * @param i
     * @return int
     */
    int left(unsigned i) { return (2 * i + 1) < m_size ? (2 * i + 1) : -1; }

    /**
     * @brief Função que retorna o índice do filho direito de um nó
     *
     * @param i
     * @return int
     */
    int right(unsigned i) { return (2 * i + 2) < m_size ? (2 * i + 2) : -1; }

    /**
     * @brief Função que troca o valor de dois nós
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
     *
     * @param new_capacity nova capacidade da fila
     */
    void reserve(unsigned new_capacity) {
        if (m_capacity < new_capacity) {
            m_capacity = new_capacity;
            int* aux = new int[m_capacity];          // aloca um novo vetor
            for (unsigned i = 0; i < m_size; ++i) {  // copia os elementos
                aux[i] = m_heap[i];
            }
            delete[] m_heap;  // libera o vetor antigo
            m_heap = aux;     // atualiza o ponteiro
        }
    }

   public:
    /**
     * @brief Construtor da classe PriorityQueue
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
     *
     */
    PriorityQueue() {
        m_capacity = 50;
        m_size = 0;
        m_heap = new int[m_capacity];
    }

    /**
     * @brief Destrutor da classe PriorityQueue
     *
     */
    ~PriorityQueue() { delete[] m_heap; }

    /**
     * @brief
     *
     * @param key
     */
    void insert(Type key) {
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
     *
     */
    void pop() {
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

    /**
     * @brief Função que retorna uma referência para o primeiro elemento da fila
     *
     * @return Type
     */
    Type front() {
        // se a heap estiver vazia, lança uma exceção
        if (m_size == 0) {
            throw std::runtime_error("Empty queue");
        }
        return m_heap[0];  // retorna o elemento de maior prioridade
    }

    /**
     * @brief
     *
     */
    void print() {
        for (unsigned i = 0; i < m_size; ++i) {
            std::cout << (Type)m_heap[i] << " ";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Função que retorna o tamanho da fila
     *
     * @return int
     */
    unsigned size() const { return m_size; }

    /**
     * @brief Função que verifica se a fila está vazia
     *
     * @return true
     * @return false
     */
    bool empty() const { return m_size == 0; }
};

#endif  // PRIORITYQUEUE_H