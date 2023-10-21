/**
 * @file Node.h
 * @author Júnior Silva (junior.silva@alu.ufc.br)
 * @author Linyker Vinicius (botlink2030@alu.ufc.br)
 * @brief Implementação da classe Node, usada para a implementação da classe
 * Queue
 * @version 0.1
 * @date 20-10-2023
 *
 *
 */

#ifndef NODE_H
#define NODE_H

template <typename Type>
class Node {
    Type data;   // dado armazenado no Node
    Node* next;  // ponteiro para o proximo Node

    /**
     * @brief Construtor da classe Node
     *
     * @param data dado a ser armazenado no Node
     * @param next ponteiro para o proximo Node
     */
    Node(Type data, Node* next);

    /**
     * @brief Destrutor da classe Node
     *
     */
    ~Node();
};

#endif  // NODE_H