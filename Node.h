#ifndef NODE_H
#define NODE_H

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
     * @brief Destroi o objeto Node
     *
     */
    ~Node() { delete next; }
};

#endif