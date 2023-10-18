#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H
#include <string>
#include <vector>

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
/**
 * @brief
 *
 */
template <typename Type>
class iterator_orderedList {
   private:
    Node<Type>* m_ptr;  // ponteiro para o no atual

   public:
    iterator_orderedList(Node<Type>* ptr) { m_ptr = ptr; }

    /**
     * @brief Sobrecarga do operador de pré-incremento.
     * Faz o iterador apontar para o proximo elemento da lista.
     *
     * @return iterator& retorna uma referencia para o iterador
     */
    iterator_orderedList& operator++() {
        m_ptr = m_ptr->next;
        return *this;
    }

    /**
     * @brief Sobrecarga do operador de pós-incremento.
     * Faz o iterador apontar para o proximo elemento da lista.
     *
     * @return iterator retorna o iterador antes de ser incrementado
     */
    iterator_orderedList operator++(int) {
        iterator_orderedList temp = *this;
        m_ptr = m_ptr->next;
        return temp;
    }

    /**
     * @brief Sobrecarga do operador de indireção.
     * Retorna o valor armazenado no Node apontado pelo iterador.
     *
     * @return Type& retorna uma referencia para o dado armazenado no Node
     */
    Type& operator*() { return m_ptr->data; }

    /**
     * @brief Sobrecarga do operador de igualdade.
     *
     * @param other iterador a ser comparado
     * @return true se os iteradores apontam para o mesmo nó
     * @return false caso contrário
     */
    bool operator==(const iterator_orderedList& other) {
        return m_ptr == other.m_ptr;
    }

    /**
     * @brief Sobrecarga do operador de desigualdade.
     *
     * @param other iterador a ser comparado
     * @return true se os iteradores apontam para nós diferentes
     * @return false caso contrário
     */
    bool operator!=(const iterator_orderedList& other) {
        return m_ptr != other.m_ptr;
    }
};

/**
 * @brief Classe que implementa a logica de uma lista duplamente encadeada
 *
 * @tparam Type
 */
template <typename Type>
class OrderedList {
   private:
    Node<Type>* m_head;  // ponteiro para o no sentinela
    Node<Type>* m_tail;  // ponteiro para o ultimo no da lista
    unsigned m_size{};

   public:
    /**
     * @brief Construtor da classe OrderedList
     *
     */
    OrderedList() {
        m_head = new Node<Type>(Type(), nullptr);
        m_tail = m_head;
        m_size = 0;
    }

    /**
     * @brief Construtor de cópia da classe OrderedList
     *
     * @param lst lista a ser copiada
     */
    OrderedList(const OrderedList& lst) {
        m_head = new Node<Type>(Type(), nullptr);
        m_tail = m_head;
        Node<Type>* aux = lst.m_head->next;
        while (aux != nullptr) {
            m_tail->next = new Node<Type>(aux->data, nullptr);
            aux = aux->next;
            m_tail = m_tail->next;
        }
        m_size = lst.m_size;
    }

    /**
     * @brief Destrutor da classe OrderedList
     *
     */
    ~OrderedList() { delete m_head; }

    /**
     * @brief Função que verifica se a lista está vazia
     *
     * @return true se a lista estiver vazia,
     * @return false caso contrário
     */
    bool isEmpyt() const { return m_size == 0; }

    /**
     * @brief Função que retorna o tamanho atual da lista
     *
     * @return int tamanho da lista
     */
    int size() const { return m_size; }

    /**
     * @brief Função que deleta todos os elementos da lista, deixando-a vazia.
     * Ao final da execução, os ponteiros m_head e m_tail devem apontar para si
     * mesmos. Complexidade: O(n)
     *
     *
     */
    void clear() { delete m_head; }

    /**
     * @brief Função que insere um elemento na lista, mantendo a ordem crescente
     *
     * @param val
     */
    void insert(const Type& val) {
        Node<Type>* new_node = new Node<Type>(val, nullptr);
        Node<Type>* aux = m_head;
        while (aux->next != nullptr && aux->next->data < val) {
            aux = aux->next;
        }
        new_node->next = aux->next;
        aux->next = new_node;
        if (new_node->next == nullptr) m_tail = new_node;
        m_size++;
    }

    /**
     * @brief Função que retorna um iterador para o primeiro elemento da lista
     *
     * @return iterator<Type>
     */
    iterator_orderedList<Type> begin() {
        return iterator_orderedList<Type>(m_head->next);
    }

    /**
     * @brief Função que retorna um iterador para o ultimo elemento da lista
     *
     * @return iterator<Type>
     */
    iterator_orderedList<Type> end() {
        return iterator_orderedList<Type>(m_tail->next);
    }
};

#endif