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

template <typename Type>
class PriorityQueue {
   private:
    int *m_heap;
    unsigned m_size;
    unsigned m_capacity;

    /**
     * @brief Função que retorna o índice do pai de um nó
     *
     * @param i
     * @return int
     */
    int parent(unsigned i);

    /**
     * @brief Função que retorna o índice do filho esquerdo de um nó
     *
     * @param i
     * @return int
     */
    int left(unsigned i);

    /**
     * @brief Função que retorna o índice do filho direito de um nó
     *
     * @param i
     * @return int
     */
    int right(unsigned i);

    /**
     * @brief Função que troca o valor de dois nós
     *
     * @param a
     * @param b
     */
    void swap(Type &a, Type &b);

    /**
     * @brief Função que corrige a heap
     *
     * @param i
     */
    void heapify(unsigned i);

    /**
     * @brief Função que aumenta a capacidade da fila. Se m_capacity >=
     * new_capacity, a funcao faz nada. Caso contrario, a funcao aumenta a
     * capacidade da fila para um valor maior ou igual a new_capacity.
     *
     * @param new_capacity nova capacidade da fila
     */
    void reserve(unsigned new_capacity);

   public:
    /**
     * @brief Construtor da classe PriorityQueue
     *
     * @param capacity
     */
    PriorityQueue(unsigned capacity);

    /**
     * @brief Construtor default da classe PriorityQueue. É aloca um vetor de 50
     * posições.
     *
     */
    PriorityQueue();

    /**
     * @brief Destrutor da classe PriorityQueue
     *
     */
    ~PriorityQueue();

    /**
     * @brief
     *
     * @param key
     */
    void insert(Type key);

    /**
     * @brief Função que remove o elemento de maior prioridade da fila
     *
     */
    void pop();

    /**
     * @brief Função que retorna uma referência para o primeiro elemento da fila
     *
     * @return Type
     */
    Type front();

    /**
     * @brief
     *
     */
    void print();

    /**
     * @brief Função que retorna o tamanho da fila
     *
     * @return int
     */
    unsigned size() const;

    /**
     * @brief Função que verifica se a fila está vazia
     *
     * @return true
     * @return false
     */
    bool empty() const;
};

#endif  // PRIORITYQUEUE_H