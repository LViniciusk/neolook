#ifndef NODE_H
#define NODE_H

/**
 * @brief Classe que implementa a lógica de um Node da lista
 */
template <typename Type>
class Node {
    // Classe amiga da classe Node
    friend class ForwardList;

   private:
    Type data;   // dado armazenado no Node
    Node* next;  // ponteiro para o proximo Node
    Node* prev;  // ponteiro para o Node anterior

   public:
    /**
     * @brief Construtor da classe Node
     *
     * @param data dado a ser armazenado no Node
     * @param next ponteiro para o proximo Node
     * @param prev ponteiro para o Node anterior
     */
    Node(Type data, Node* next = nullptr, Node* prev = nullptr) {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }

    /**
     * @brief Destroi o objeto Node
     *
     */
    ~Node() {
        this->next = nullptr;
        this->prev = nullptr;
    }
};

#endif