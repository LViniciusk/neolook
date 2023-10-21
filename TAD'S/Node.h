/**
 * @file Node.h
 * @author Júnior Silva (junior.silva@alu.ufc.br)
 * @author Linyker Vinicius (botlink2030@alu.ufc.br)
 * @brief Implementação da classe Node, usada na implementação da classe Queue
 * @version 0.1
 * @date 20-10-2023
 *
 *
 */

#ifndef NODE_H
#define NODE_H

/**
 * @brief Estrutura que define um nó em uma lista encadeada.
 *
 * Esta estrutura representa um nó em uma lista encadeada simples. Cada nó
 * contém um valor e um ponteiro para o próximo nó na lista.
 * Esta estrutura é usada na implementação da classe Queue.
 *
 * @tparam Type
 */
template <typename Type>
struct Node {
    Type data;   // dado armazenado no Node
    Node* next;  // ponteiro para o proximo Node

    /**
     * @brief Construtor da classe Node
     *
     * @param data dado a ser armazenado no Node
     * @param next ponteiro para o proximo Node
     */
    Node(Type data, Node* next) {
        this->data = data;
        this->next = next;
    }

    /**
     * @brief Destrutor da classe Node
     *
     * Este método é responsável por liberar a memória alocada para o Node e
     * seus nós subsequentes.
     */
    ~Node() { delete next; }
};

#endif  // NODE_H
