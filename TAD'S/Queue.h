/**
 * @file Queue.h
 * @author Júnior Silva (junior.silva@alu.ufc.br) - 554222
 * @author Linyker Vinicius (botlink2030@alu.ufc.br) - 556280
 * @brief Implementação de uma Queue para tipo genérico
 * @version 0.1
 * @date 20-10-2023
 *
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

#include "Node.h"

template <typename Type>
class iterator_queue {
   private:
    Node<int> *m_ptr;  // ponteiro para o no atual

   public:
    /**
     * @brief Construtor da classe iterator_queue
     * Complexidade: O(1)
     *
     * @param ptr
     */
    iterator_queue(Node<Type> *ptr) { m_ptr = ptr; }

    /**
     * @brief Sobrecarga do operador de pré-incremento.
     * Faz o iterador apontar para o proximo elemento da lista.
     * Complexidade: O(1)
     *
     * @return iterator& retorna uma referencia para o iterador
     */
    iterator_queue &operator++() {
        m_ptr = m_ptr->next;
        return *this;
    }

    /**
     * @brief Sobrecarga do operador de pós-incremento.
     * Faz o iterador apontar para o proximo elemento da lista.
     * Complexidade: O(1)
     *
     * @return iterator retorna o iterador antes de ser incrementado
     */
    iterator_queue operator++(int) {
        iterator_queue temp = *this;
        m_ptr = m_ptr->next;
        return temp;
    }

    /**
     * @brief Sobrecarga do operador de indireção.
     * Retorna o valor armazenado no Node apontado pelo iterador.
     * Complexidade: O(1)
     *
     * @return Type& retorna uma referencia para o dado armazenado no Node
     */
    Type &operator*() { return m_ptr->data; }

    /**
     * @brief Sobrecarga do operador de igualdade.
     * Complexidade: O(1)
     *
     * @param other iterador a ser comparado
     * @return true se os iteradores apontam para o mesmo nó
     * @return false caso contrário
     */
    bool operator==(const iterator_queue &other) {
        return m_ptr == other.m_ptr;
    }

    /**
     * @brief Sobrecarga do operador de desigualdade.
     * Complexidade: O(1)
     *
     * @param other iterador a ser comparado
     * @return true se os iteradores apontam para nós diferentes
     * @return false caso contrário
     */
    bool operator!=(const iterator_queue &other) {
        return m_ptr != other.m_ptr;
    }
};

/**
 * @file Queue.h
 * @brief Esse arquivo contém a implementação de uma fila para tipo genérico
 *
 * Uma fila é uma estrutura de dados linear que segue a ordem "Primeiro a
 * Entrar, Primeiro a Sair" (FIFO - First In, First Out). Ela mantém uma coleção
 * de elementos onde a remoção de elementos ocorre no início da fila e a
 * inserção de elementos ocorre no final da fila.
 *
 */
template <typename Type>
class Queue {
   private:
    Node<Type> *m_head;  // ponteiro para o no sentinela
    Node<Type> *m_tail;  // ponteiro para o ultimo nó da fila
    unsigned m_size{};   // quantidade de elementos na fila

   public:
    /**
     * @brief Construtor da classe Queue. Cria uma fila vazia.
     * Complexidade: O(1)
     *
     */
    Queue() {
        m_head = new Node<Type>(Type(), nullptr);
        m_tail = m_head;
        m_size = 0;
    }

    /**
     * @brief Construtor de cópia da classe Queue
     * Complexidade: O(n)
     *
     * @param lst - fila a ser copiada
     */
    Queue(const Queue &lst) {
        m_head = new Node<Type>(Type(), nullptr);
        Node<Type> *aux = lst.m_head;
        while (aux != nullptr) {
            push(aux->data);
            aux = aux->next;
        }
        m_size = lst.m_size;
    }

    /**
     * @brief Destrutor da classe Queue.
     * Libera toda a memoria alocada, ate mesmo o nó sentinela
     * Complexidade: O(n)
     *
     */
    ~Queue() { delete m_head; }

    /**
     * @brief Funçãi que verifica se uma lista está vazia.
     * Complexidade: O(1)
     *
     * @return true se a lista está vazia,
     * @return false caso contrário
     */
    bool empty() const { return m_size == 0; }

    /**
     * @brief Função que retorna o número de elementos na fila
     * Complexidade: O(1)
     *
     * @return unsigned int
     */
    unsigned int size() const { return m_size; }

    /**
     * @brief Função que remove todos os elementos da lista: size() == 0
     * Complexidade: O(n)
     *
     */
    void clear() {
        while (m_size > 0) {
            pop();
        }
    }

    /**
     * @brief Função que insere um elemento na fila. O elemento é inserido no
     * final da fila.
     * Complexidade: O(1)
     *
     * @param val - valor a ser inserido
     */
    void push(const Type &val) {
        Node<Type> *aux = new Node<Type>(val, nullptr);
        if (m_size > 0) {
            m_tail->next = aux;
            m_tail = aux;
        } else {
            m_tail = m_head = aux;
        }
        m_size++;
    }

    /**
     * @brief Função que retorna uma referencia para o primeiro elemento da fila
     * Complexidade: O(1)
     *
     * @return Type&
     */
    Type &front() {
        if (m_size == 0) throw std::runtime_error("empty queue");
        return m_head->data;
    }

    /**
     * @brief Função que retorna uma referencia para o primeiro elemento da fila
     * Complexidade: O(1)
     *
     * @return const Type&
     */
    const Type &front() const {
        if (m_size == 0) throw std::runtime_error("empty queue");
        return m_head->data;
    }

    /**
     * @brief Função que remove o primeiro elemento da fila
     * Complexidade: O(1)
     *
     */

    void pop() {
        if (m_size == 0) throw std::runtime_error(" empty queue ");
        Node<Type> *aux = m_head;
        m_head = aux->next;
        aux->next = nullptr;
        delete aux;
        m_size--;
    }

    /**
     * @brief Função que retorna uma referencia para o último elemento da
     * fila
     * Complexidade: O(1)
     *
     * @return Type&
     */
    Type &back() {
        if (m_size == 0) throw std::runtime_error("empty queue");
        return m_tail->data;
    }

    /**
     * @brief Função que retorna uma referencia para o último elemento da
     * fila
     * Complexidade: O(1)
     *
     * @return const Type&
     */
    const Type &back() const {
        if (m_size == 0) throw std::runtime_error("empty queue");
        return m_tail->data;
    }
    /**
     * @brief Função que retorna um iterador que aponta para o primeiro
     * elemento da fila
     * Complexidade: O(1)
     *
     * @return iterator_queue<Type>
     */
    iterator_queue<Type> begin() { return iterator_queue<Type>(m_head); }

    /**
     * @brief Função que retorna um iterador que aponta para o primeiro bit
     * após o último elemento da fila
     * Complexidade: O(1)
     *
     * @return iterator_queue<Type>
     */
    iterator_queue<Type> end() { return iterator_queue<Type>(m_tail->next); }
};

#endif  // QUEUE_H