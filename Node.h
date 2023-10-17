#ifndef NODE_H
#define NODE_H

/**
 * @brief Classe que implementa a logica de um Node da lista 
 */
class Node {
    // Classe amiga da classe Node
    friend class ForwardList;

private:
    int data;    // valor a ser armazenado 
    Node* next;  // ponteiro para o proximo node 
    Node* prev;  // ponteiro para o node anterior

public:
    // Construtor 
    Node(const int& val, Node *prevPrt, Node *nextPtr) {
        data = val;
        prev = prevPrt;
        next = nextPtr;
    }
};

#endif