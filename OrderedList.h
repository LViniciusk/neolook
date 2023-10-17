#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H
#include <vector>
#include <string>
#include "Node.h"

/**
 * @brief Classe que implementa a logica de uma lista simplesmente encadeada
 * Essa lista possui um ponteiro m_head para o node sentinela, que marca o inicio da lista,
 * mas diferentemente do que foi feito em sala, nao possui um ponteiro m_tail para o ultimo elemento.
 */
class OrderedList {
private:
    /**
     * m_head: ponteiro para o inicio da lista.
     * O ponteiro m_head sempre aponta para um no sentinela.
     */
    Node* m_head {}; 
    /**
     * m_size: numero de elementos na lista 
     */
    unsigned m_size {};  
    
public:
    // construtor: cria lista vazia
    OrderedList();

    // construtor de copia
    OrderedList(const OrderedList& lst);

    // retorna true se e somente se a lista esta vazia
    bool empty() const;

    // retorna o numero de elementos na lista
    int size() const;

    // deixa a lista vazia: size() == 0
    void clear();

    // destrutor: libera toda a memoria alocada, ate mesmo o no sentinela
    ~OrderedList();

    // Imprime a lista no terminal
    void print() const;


    // --------------------------------------------------------- //
    // ----------- funcoes adicionais - parte 1 ---------------- //
    // --------------------------------------------------------- //

    // insere um elemento no inicio da lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    void push_front(const int& val);

    // retorna uma referencia para o primeiro elemento na lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    int& front();
    const int& front() const;

    // deleta o primeiro elemento da lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    void pop_front();

    // retorna uma referencia para o ultimo elemento na lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    int& back();
    const int& back() const;
    
    // insere um elemento no final da lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    void push_back(const int& val);

    // deleta o ultimo elemento da lista
    // Restricao: estar proibido usar funções auxiliares nesta questao,
    // inclusive qualquer dos operadores sobrecarregados
    void pop_back();

};

#endif