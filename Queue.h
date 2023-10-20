#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>
#include <string>
#include <vector>

#include "Node.h"

/**
 * @brief Classe que implementa um iterador para a classe Queue
 *
 */
template <typename Type>
class iterator_queue {
   private:
    Node<int> *m_ptr;  // ponteiro para o no atual
   public:
    /**
     * @brief Construtor da classe iterator_queue
     *
     * @param ptr
     */
    iterator_queue(Node<Type> *ptr);

    /**
     * @brief Sobrecarga do operador de pré-incremento.
     * Faz o iterador apontar para o proximo elemento da lista.
     *
     * @return iterator& retorna uma referencia para o iterador
     */
    iterator_queue &operator++();

    /**
     * @brief Sobrecarga do operador de pós-incremento.
     * Faz o iterador apontar para o proximo elemento da lista.
     *
     * @return iterator retorna o iterador antes de ser incrementado
     */
    iterator_queue operator++(int);

    /**
     * @brief Sobrecarga do operador de indireção.
     * Retorna o valor armazenado no Node apontado pelo iterador.
     *
     * @return Type& retorna uma referencia para o dado armazenado no Node
     */
    Type &operator*();

    /**
     * @brief Sobrecarga do operador de igualdade.
     *
     * @param other iterador a ser comparado
     * @return true se os iteradores apontam para o mesmo nó
     * @return false caso contrário
     */
    bool operator==(const iterator_queue &other);

    /**
     * @brief Sobrecarga do operador de desigualdade.
     *
     * @param other iterador a ser comparado
     * @return true se os iteradores apontam para nós diferentes
     * @return false caso contrário
     */
    bool operator!=(const iterator_queue &other);
};

template <typename Type>
class Queue {
   private:
    Node<Type> *m_head;  // ponteiro para o no sentinela
    Node<Type> *m_tail;  // ponteiro para o ultimo nó da fila
    unsigned m_size{};   // quantidade de elementos na fila

   public:
    /**
     * @brief Construtor da classe Queue. Cria uma fila vazia.
     *
     */
    Queue();

    /**
     * @brief Construtor de cópia da classe Queue
     *
     * @param lst - fila a ser copiada
     */
    Queue(const Queue &lst);

    /**
     * @brief Destrutor da classe Queue.
     * Libera toda a memoria alocada, ate mesmo o nó sentinela
     *
     */
    ~Queue();

    /**
     * @brief Funçãi que verifica se uma lista está vazia.
     *
     * @return true se a lista está vazia,
     * @return false caso contrário
     */
    bool empty() const;

    /**
     * @brief Função que retorna o número de elementos na fila
     *
     * @return unsigned int
     */
    unsigned int size() const;

    /**
     * @brief Função que remove todos os elementos da lista: size() == 0
     *
     */
    void clear();

    /**
     * @brief Função que insere um elemento na fila. O elemento é inserido no
     * final da fila.
     *
     * @param val - valor a ser inserido
     */
    void push(const int &val);

    /**
     * @brief Função que retorna uma referencia para o primeiro elemento da fila
     *
     * @return int&
     */
    int &front();

    /**
     * @brief Função que retorna uma referencia para o primeiro elemento da fila
     *
     * @return const int&
     */
    const int &front() const;

    /**
     * @brief Função que remove o primeiro elemento da fila
     *
     */

    void pop();

    /**
     * @brief Função que retorna uma referencia para o último elemento da
     * fila
     *
     * @return int&
     */
    int &back();

    /**
     * @brief Função que retorna uma referencia para o último elemento da
     * fila
     *
     * @return const int&
     */
    const int &back() const;
    /**
     * @brief Função que retorna um iterador que aponta para o primeiro
     * elemento da fila
     *
     * @return iterator_queue<Type>
     */
    iterator_queue<Type> begin();

    /**
     * @brief Função que retorna um iterador que aponta para o primeiro bit
     * após o último elemento da fila
     *
     * @return iterator_queue<Type>
     */
    iterator_queue<Type> end();
};

#endif