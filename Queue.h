#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include <string>
#include <stdexcept>
#include "Node.h"







template <typename Type>
class Queue {
private:
    Node<Type>* m_head;  // ponteiro para o no sentinela
    Node<Type>* m_tail;  // ponteiro para o ultimo nó da fila
    unsigned m_size{};   // quantidade de elementos na fila
    
public:
    // construtor: cria fila vazia
    Queue(){
        m_head = new Node<Type>(Type(), nullptr);
        m_tail = m_head;
        m_size = 0;
    }

    // construtor de copia
    Queue(const Queue& lst){
        m_head = new Node<Type>(Type(), nullptr);
        Node<Type>* aux = lst.m_head;
        while (aux != nullptr) {
            push(aux->data);
            aux = aux->next;
        }
        m_size = lst.m_size;
    }

    // destrutor: libera toda a memoria alocada, ate mesmo o nó sentinela
    ~Queue() { delete m_head; }

    // retorna true se e somente se a lista esta vazia
    bool empty() const{
        return m_head->next ==  nullptr;
    }

    // retorna o numero de elementos na lista
    unsigned int size() const{
        return m_size;
    }

    // deixa a lista vazia: size() == 0
    void clear(){
        delete m_head;
    }



    void push(const int& val){
        Node<Type>* aux = new Node<Type>(val, nullptr);
        if(m_size > 0){
            m_tail->next = aux;
            m_tail = aux;
        }else{
            m_tail = m_head = aux;
        }
        m_size++;
    }

    int& front(){
        if(m_size == 0) throw std::runtime_error (" empty queue ");
        return m_head->data;
    }
    const int& front() const{
        if(m_size == 0) throw std::runtime_error (" empty queue ");
        return m_head->data;
    }

    void pop(){
        if(m_size == 0) throw std::runtime_error (" empty queue ");
        Node<Type> *aux = m_head;
        m_head = aux->next;
        aux->next = nullptr;
        delete aux;
        m_size--;
    }


    int& back(){
        if(m_size == 0) throw std::runtime_error (" empty queue ");
        return m_tail->data;
    }
    const int& back() const{
        if(m_size == 0) throw std::runtime_error (" empty queue ");
        return m_tail->data;
    }


};

#endif